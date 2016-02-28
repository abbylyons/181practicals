# Example Feature Extraction from XML Files
# We count the number of specific system calls made by the programs, and use
# these as our features.

# This code requires that the unzipped training set is in a folder called "train".

import os
from collections import Counter
try:
    import xml.etree.cElementTree as ET
except ImportError:
    import xml.etree.ElementTree as ET
import numpy as np
from scipy import sparse
import util as ut
from sklearn.ensemble import RandomForestClassifier
from sklearn.cross_validation import cross_val_score
from sklearn.grid_search import GridSearchCV

import util

TRAIN_DIR = "train"
TEST_DIR = "test"

call_set = set([])

def add_to_set(tree):
    for el in tree.iter():
        call = el.tag
        call_set.add(call)

def create_data_matrix(start_index, end_index, direc="train"):
    X = None
    classes = []
    ids = []
    i = -1
    for datafile in os.listdir(direc):
        if datafile == '.DS_Store':
            continue

        i += 1
        if i < start_index:
            continue
        if i >= end_index:
            break

        # extract id and true class (if available) from filename
        id_str, clazz = datafile.split('.')[:2]
        ids.append(id_str)
        # add target class if this is training data
        try:
            classes.append(util.malware_classes.index(clazz))

        except ValueError:
            # we should only fail to find the label in our list of malware classes
            # if this is test data, which always has an "X" label
            assert clazz == "X"
            classes.append(-1)
        # parse file as an xml document
        tree = ET.parse(os.path.join(direc,datafile))
        add_to_set(tree)
        this_row = np.append(find_call_distribution(tree), seek_vba(tree))
        print this_row
        if X is None:
            X = this_row
        else:
            X = np.vstack((X, this_row))
    return X, np.array(classes), ids

def find_call_distribution(tree):
    all_calls = ['processes', 'process', 'thread', 'all_section', 'load_image', 'load_dll', 'open_key', 'get_file_attributes', 'vm_protect', 'create_file', 'set_file_attributes', 'open_file', 'query_value', 'find_file', 'check_for_debugger', 'create_process', 'delete_file', 'kill_process', 'enum_window', 'create_mutex', 'create_thread', 'get_system_directory', 'enum_keys', 'get_username', 'create_key', 'set_value', 'vm_allocate', 'vm_write', 'create_thread_remote', 'create_open_file', 'get_host_by_name', 'set_windows_hook', 'create_window', 'get_computer_name', 'impersonate_user', 'open_scmanager', 'create_socket', 'bind_socket', 'connect_socket', 'send_socket', 'dump_line', 'recv_socket', 'trimmed_bytes', 'open_url', 'sleep', 'open_mutex', 'open_service', 'enum_values', 'get_windows_directory', 'find_window', 'enum_modules', 'enum_processes', 'copy_file', 'read_value', 'write_value', 'get_system_time', 'com_create_instance', 'com_get_class_object', 'move_file', 'control_service', 'start_service', 'create_namedpipe', 'delete_value', 'create_directory', 'connect', 'message', 'show_window', 'destroy_window', 'set_file_time', 'open_process', 'enum_share', 'create_process_as_user', 'revert_to_self', 'remove_directory', 'delete_key', 'download_file', 'listen_socket', 'add_netjob', 'change_service_config', 'create_service', 'read_section', 'download_file_to_cache', 'set_thread_context', 'create_interface', 'enum_types', 'enum_subtypes', 'enum_items', 'vm_read', 'delete_share', 'logon_as_user', 'load_driver', 'enum_handles', 'create_mailslot', 'create_process_nt', 'exit_windows', 'get_host_by_addr', 'accept_socket', 'com_createole_object', 'set_system_time', 'delete_service', 'unload_driver', 'read_section_names', 'vm_mapviewofsection', 'enum_user', 'get_userinfo', 'enum_services']
    distribution = [0.0]*len(all_calls)
    count = 0.0
    for el in tree.iter():
        if el.tag in all_calls:
            distribution[all_calls.index(el.tag)] += 1.0
        count += 1.0
    return np.divide(np.array(distribution), count)

def seek_tdss(tree):
    target_call = "vm_protect"
    count = 0
    for el in tree.iter():
        if el.tag == target_call:
            count += 1
    return count


def seek_vba(tree):
    target_call = "open_key"
    VBA_key = "HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\VBA\Monitors"

    for el in tree.iter():
        if el.tag == target_call:
            if el.get("key") == VBA_key:
                return 1
    return 0


def call_feats(tree):
    good_calls = ['sleep', 'dump_line']

    call_counter = {}
    for el in tree.iter():
        call = el.tag
        if call not in call_counter:
            call_counter[call] = 0
        else:
            call_counter[call] += 1

    call_feat_array = np.zeros(len(good_calls))
    for i in range(len(good_calls)):
        call = good_calls[i]
        call_feat_array[i] = 0
        if call in call_counter:
            call_feat_array[i] = call_counter[call]

    return call_feat_array

## Feature extraction
def main():
    X_train, t_train, train_ids = create_data_matrix(0, 3086, TRAIN_DIR)
    # X_valid, t_valid, valid_ids = create_data_matrix(1000, 2000, TRAIN_DIR)
    X_test, t_test, test_ids = create_data_matrix(0,3724, TEST_DIR)

    # print 'Data matrix (training set):'
    # print np.array(X_train)
    # print 'Classes (training set):'
    # print np.array(t_train)

    clf = RandomForestClassifier(n_estimators=20, max_depth = None, max_features =1, criterion = "gini", min_samples_split = 1, min_samples_leaf = 1, bootstrap = False)
    # use a full grid over all parameters
    param_grid = {"max_depth": [3, None],
              "max_features": [1, 3, 10],
              "min_samples_split": [1, 3, 10],
              "min_samples_leaf": [1, 3, 10],
              "bootstrap": [True, False],
              "criterion": ["gini", "entropy"]}

    # # run grid search
    # grid_search = GridSearchCV(clf, param_grid=param_grid)
    # grid_search.fit(X_train, t_train)
    # preds = grid_search.predict(X_test)
    # print grid_search.best_params_

    clf = clf.fit(X_train, t_train)
    preds = clf.predict(X_test)
    ut.write_predictions(preds, test_ids, "result.csv")

if __name__ == "__main__":
    main()

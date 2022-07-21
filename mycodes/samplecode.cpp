#include <cassert>
#include <iostream>
#include <string>
#include <rocksdb/db.h>

using namespace std;

int main(int argc, char** argv) {
    cout << "1" << endl;
    rocksdb::DB* db=NULL;
    cout << "2" << endl;
    rocksdb::Options options;
    cout << "3" << endl;
    options.create_if_missing = true;
    cout << "4" << endl;
    rocksdb::Status status;
    cout << "5" << endl;
    status = rocksdb::DB::Open(options, "/home/jaepark/testdb", &db);
    assert(status.ok());
    cout << "6" << endl;
    // Insert value
    status = db->Put(rocksdb::WriteOptions(), "Test key", "Test value");
    assert(status.ok());
    // Read back value
    std::string value;
    status = db->Get(rocksdb::ReadOptions(), "Test key", &value);
    assert(status.ok());
    assert(!status.IsNotFound());
    // Read key which does not exist
    status = db->Get(rocksdb::ReadOptions(), "This key does not exist", &value);
    assert(status.IsNotFound());
}

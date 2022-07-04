// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include <cstdio>
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"

using ROCKSDB_NAMESPACE::DB;
using ROCKSDB_NAMESPACE::Options;
using ROCKSDB_NAMESPACE::PinnableSlice;
using ROCKSDB_NAMESPACE::ReadOptions;
using ROCKSDB_NAMESPACE::Status;
using ROCKSDB_NAMESPACE::WriteBatch;
using ROCKSDB_NAMESPACE::WriteOptions;

#if defined(OS_WIN)
std::string kDBPath = "C:\\Windows\\TEMP\\rocksdb_simple_example";
#else
std::string kDBPath = "/tmp/ycsb-rocksdb";
#endif

class ZipfGenerator
{
    public:
    int alpha;
    int n;

    ZipfGenerator()
};

int main() {
  DB* db;
  Options options;
  std::fstream outfile;
  options.create_if_missing = true;

  // open DB
  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());
  std::string value;
  int count = 0;

  /* Iterate over each item in the database */
  rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
  for (it->SeekToFirst(); it->Valid(); it->Next())
  {
      // std::cout << it->key().ToString() << std::endl;  /* print out key */
      db->Get(rocksdb::ReadOptions(), it->key(), &value);  /* read key */
      count++;
      if (count % 100000 == 0 && count) {std::cout << "count: " << count << std::endl;}
  }
  std::cout << "total: " << count << std::endl;

  if(false == it->status().ok())
  {
      std::cerr << "Error during the scan" << std::endl;
      std::cerr << it->status().ToString() << std::endl;
  }



  delete db;

  return 0;
}
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
std::string kDBPath = "/mnt/c/DB/ycsb-rocksdb";
#endif

int main() {
  DB* db;
  Options options;
  // // options.create_if_missing = true;
  // open DB
  Status s = DB::Open(options, kDBPath, &db);
  assert(s.ok());
  //ANCHOR
  // std::string value;
  // std::string randomval(1000, '0');
  // // Optimize RocksDB. This is the easiest way to get RocksDB to perform well
  // // options.IncreaseParallelism();
  // // options.OptimizeLevelStyleCompaction();
  // // create the DB if it's not already present
  // std::ifstream ifile("updatelist.txt");
  // std::string str;
  // while(std::getline(ifile, str)){
  //   //process string
  //   //Put key-value
  //   s = db->Put(WriteOptions(), str, randomval);
  //   assert(s.ok());
  // }
  // ifile.close();

  // ifile.open("updatelist.txt");
  // while(std::getline(ifile, str)){
  //   //process string
  //   //get key-value
  //   s = db->Get(ReadOptions(), str, &value);
  //   assert(s.ok());
  //   std::cout << value << std::endl;
  // }
  // ifile.close();
  //ANCHOR
  //clock_t start, end;
  //start = clock();

  // Put key-value
  //s = db->Put(WriteOptions(), "key1", "value");
  // assert(s.ok());
  // // get value
  // s = db->Get(ReadOptions(), "key1", &value);
  // assert(s.ok());
  // assert(value == "value");

  // // atomically apply a set of updates
  // {
  //   WriteBatch batch;
  //   batch.Delete("key1");
  //   batch.Put("key2", value);
  //   s = db->Write(WriteOptions(), &batch);
  // }

  // s = db->Get(ReadOptions(), "key1", &value);
  // assert(s.IsNotFound());

  // db->Get(ReadOptions(), "key2", &value);
  // assert(value == "value");

  // {
  //   PinnableSlice pinnable_val;
  //   db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
  //   assert(pinnable_val == "value");
  // }

  // {
  //   std::string string_val;
  //   // If it cannot pin the value, it copies the value to its internal buffer.
  //   // The intenral buffer could be set during construction.
  //   PinnableSlice pinnable_val(&string_val);
  //   db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
  //   assert(pinnable_val == "value");
  //   // If the value is not pinned, the internal buffer must have the value.
  //   assert(pinnable_val.IsPinned() || string_val == "value");
  // }

  // PinnableSlice pinnable_val;
  // s = db->Get(ReadOptions(), db->DefaultColumnFamily(), "key1", &pinnable_val);
  // assert(s.IsNotFound());
  // // Reset PinnableSlice after each use and before each reuse
  // pinnable_val.Reset();
  // db->Get(ReadOptions(), db->DefaultColumnFamily(), "key2", &pinnable_val);
  // assert(pinnable_val == "value");
  // pinnable_val.Reset();
  // // The Slice pointed by pinnable_val is not valid after this point

  // db->GetProperty("rocksdb.num-files-at-level0", &value);
  // std::cout << value << std::endl;
  // db->GetProperty("rocksdb.num-files-at-level1", &value);
  // std::cout << value << std::endl;
  // db->GetProperty("rocksdb.num-files-at-level2", &value);
  // std::cout << value << std::endl;
  // db->GetProperty("rocksdb.num-files-at-level3", &value);
  // std::cout << value << std::endl;
  // for(int i = 0; i < 5; ++i){
  //   end = clock();
  //   double result = end - start;
  //   while(result < 5 * (i + 1)){
  //     end = time(NULL);
  //     result - end - start;
  //   }
  // int i = 0;
  // while(1){
  //   i++;
  // }
  // std::cout << "dbstats" << std::endl;
  // db->GetProperty("rocksdb.dbstats", &value);
  // std::cout << value << std::endl;
  // std::cout << "levelstats" << std::endl;
  // db->GetProperty("rocksdb.levelstats", &value);
  // std::cout << value << std::endl;
  // std::cout << "stats" << std::endl;
  // db->GetProperty("rocksdb.stats", &value);
  // std::cout << value << std::endl;
  // }
  // std::map<std::string, std::string> mvalue;
  // db->GetMapProperty(DB::Properties::kBlockCacheEntryStats, &mvalue);
  // for(auto it = mvalue.begin(); it != mvalue.end(); ++it){
  //   std::cout << it->first << " " << it->second << " " << std::endl;
  // }


  delete db;

  return 0;
}

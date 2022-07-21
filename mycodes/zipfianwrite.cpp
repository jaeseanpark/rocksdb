// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#include <cstdio>
#include <string>
#include <iostream>
#include <time.h>
#include <fstream>
#include <math.h>
#include <vector>
#include <algorithm>

#include "rocksdb/db.h"
#include "rocksdb/slice.h"
#include "rocksdb/options.h"
//ANCHOR
#define NUM_KEYS 100 
#define NUM_REQUESTS 1000 
//ANCHOR
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
template<class T, size_t N>
constexpr size_t size(T (&)[N]) {return N;}

class ZipfGenerator
{
    public:
    int alpha;
    int n;

    ZipfGenerator();
};

void cumsum(double* arr){
  for(int i = 1; i < NUM_KEYS; i++)
    arr[i] += arr[i-1];
}

double* make_zipfian_array(){
  int* result;
  double alpha = 0.1;
  result = (int*)calloc(NUM_KEYS, sizeof(int));
  double* tmp = (double*)calloc(NUM_KEYS+1, sizeof(double));
  for(int i = 1; i < NUM_KEYS+1; i++){
    tmp[i-1] = 1 / (pow((float)i, alpha));
  }

  std::cout << "tmp" << std::endl;
  for(int i = 0; i < NUM_KEYS; i++){
    printf("%lf\n", tmp[i]);
  }

  cumsum(tmp);
  std::cout << "zeta" << std::endl;
  for(int i = 0; i < NUM_KEYS; i++){
    printf("%lf\n", tmp[i]);
  }

  for(int i = 0; i < NUM_KEYS; i++){
    tmp[i] = tmp[i] / tmp[NUM_KEYS -1];
  }
  std::cout << "distMap" << std::endl;
  for(int i = 0; i < NUM_KEYS; i++){
    printf("%lf\n", tmp[i]);
  }

  result[0] = tmp[0] * NUM_REQUESTS;
  for(int i = 1; i < NUM_KEYS; i++){
    result[i] = round((tmp[i] - tmp[i-1]) * NUM_REQUESTS);
  }
  std::cout << "result" << std::endl;
  for(int i = 0; i < NUM_KEYS; i++){
    printf("%d\n", result[i]);
  }

  return tmp;
}

int main() {
  DB* db;
  Options options;
  std::fstream outfile;
  int n;
  options.create_if_missing = true;
  std::vector<int>::iterator low1;
  srand((unsigned)time(NULL));
  int countarray[10] = {0};
  double temp;
  //ANCHOR
  double* distmap = make_zipfian_array();
  for (int i = 0; i < 1000; i++){
    temp = (double)rand()/RAND_MAX;
    double (*idx) = std::upper_bound(&distmap[0], &distmap[0] + 10, temp);
    switch(idx-distmap){
      case 0: countarray[0]++;
      break;
      case 1: countarray[1]++;
      break;
      case 2: countarray[2]++;
      break;
      case 3: countarray[3]++;
      break;
      case 4: countarray[4]++;
      break;
      case 5: countarray[5]++;
      break;
      case 6: countarray[6]++;
      break;
      case 7: countarray[7]++;
      break;
      case 8: countarray[8]++;
      break;
      case 9: countarray[9]++;
      break;
    }
  }
  for (int i = 0; i < 100; i++)
    std::cout << "\n" << countarray[i] << std::endl;
  //ANCHOR

  // open DB
//   Status s = DB::Open(options, kDBPath, &db);
//   assert(s.ok());
//   std::string value;
//   int count = 0;

//   /* Iterate over each item in the database */
//   rocksdb::Iterator* it = db->NewIterator(rocksdb::ReadOptions());
//   for (it->SeekToFirst(); it->Valid(); it->Next())
//   {
//       // std::cout << it->key().ToString() << std::endl;  /* print out key */
//       db->Get(rocksdb::ReadOptions(), it->key(), &value);  /* read key */
//       count++;
//       if (count % 100000 == 0 && count) {std::cout << "count: " << count << std::endl;}
//   }
//   std::cout << "total: " << count << std::endl;

//   if(false == it->status().ok())
//   {
//       std::cerr << "Error during the scan" << std::endl;
//       std::cerr << it->status().ToString() << std::endl;
//   }



//   delete db;

  return 0;
}

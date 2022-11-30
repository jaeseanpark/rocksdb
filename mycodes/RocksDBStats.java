import java.lang.IllegalArgumentException;
import java.util.Arrays;
import java.util.List;
import java.util.Map;
import java.util.ArrayList;

import org.rocksdb.*;
import org.rocksdb.util.SizeUnit;

public class RocksDBStats {
    public static void main(final String[] args){
        if (args.length < 1){
            System.out.println("usage: RocksDBSample db_path");
            System.exit(-1);
        }
        final String db_path = args[0];
        RocksDB.loadLibrary();
        try (
        // final Options options = new Options();
        final Filter bloomFilter = new BloomFilter(10);
        final ReadOptions readOptions = new ReadOptions()
            .setFillCache(false);
        final Statistics stats = new Statistics();
        final RateLimiter rateLimiter = new RateLimiter(10000000,10000, 10);
        final ColumnFamilyOptions cfOpts = new ColumnFamilyOptions()
            .optimizeLevelStyleCompaction()
            .setMaxBytesForLevelBase(134217728)) {

            // options.setCreateIfMissing(true);
            final DBOptions dboptions = new DBOptions().setCreateIfMissing(true);
            final List<ColumnFamilyDescriptor> cfDescriptors = Arrays.asList(
                new ColumnFamilyDescriptor(RocksDB.DEFAULT_COLUMN_FAMILY, cfOpts),
                new ColumnFamilyDescriptor("usertable".getBytes(), cfOpts));

            final List<ColumnFamilyHandle> columnFamilyHandleList = new ArrayList<>();

            try (final RocksDB db = RocksDB.open(dboptions, db_path, cfDescriptors, columnFamilyHandleList)) {
                // db.put("hello".getBytes(), "world".getBytes());
        
                // final byte[] value = db.get("hello".getBytes());
                // assert ("world".equals(new String(value)));
                // System.out.println("Retrieved value: " + new String(value));
                final String str = db.getProperty(columnFamilyHandleList.get(1), "rocksdb.stats");
                assert (str != null && !str.equals(""));
                System.out.println(str);
                final String levelstats = db.getProperty(columnFamilyHandleList.get(1), "rocksdb.levelstats");
                assert (str != null && !str.equals(""));
                System.out.println(levelstats);
            } catch (final RocksDBException e) {
                System.out.format("[ERROR] caught the unexpected exception -- %s\n", e);
                assert (false);
            }
        }
    }
}

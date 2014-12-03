#include <gtest-strip.h>
#include "libtorrentaccessor.h"

class LibtorrentAccessorTest : public ::testing::Test
{
protected:
    LibtorrentAccessorTest() {
        ira = new LibtorrentAccessor();
    }

    ~LibtorrentAccessorTest() {
        delete ira;
    }

    IRecordsAccessor *getAccessor() const { return ira; }

    IRecordsAccessor *getConfigedAccessor() {
        QVariantHash args;
        args["configDir"] = "data/libtorrent/config";
        args["backupDir"] = "data/libtorrent/backup";
        ira->setup(args);
        return ira;
    }

    IRecordsAccessor *ira = nullptr;
};

TEST_F(LibtorrentAccessorTest, Setup)
{
    IRecordsAccessor *ira = getAccessor();
    QVariantHash args;
    args["configDir"] = "data/libtorrent/config";
    args["backupDir"] = "data/libtorrent/backup";
    EXPECT_EQ(true, ira->setup(args)) << "setup failed";
}

TEST_F(LibtorrentAccessorTest, ReadAll)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    QList<TorrentRecord> list;
    EXPECT_EQ(true, ira->readAll(list)) << "readAll failed";

    EXPECT_EQ(19, list.size());
}

TEST_F(LibtorrentAccessorTest, WriteAll)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    QList<TorrentRecord> list;
    EXPECT_EQ(true, ira->writeAll(list)) << "writeAll failed";
}

TEST_F(LibtorrentAccessorTest, Add)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    TorrentRecord re;
    EXPECT_EQ(true, ira->add(re)) << "add failed";
}

TEST_F(LibtorrentAccessorTest, Update)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    TorrentRecord re;
    EXPECT_EQ(true, ira->update(re)) << "update failed";
}

TEST_F(LibtorrentAccessorTest, Remove)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    QString hash("e3c1533f92df93db60a5c139dfc22a53e4995be1");
    EXPECT_EQ(true, ira->remove(hash)) << "remove failed";

    QList<TorrentRecord> list;
    ASSERT_EQ(true, ira->readAll(list));
    EXPECT_EQ(18, list.size());
}

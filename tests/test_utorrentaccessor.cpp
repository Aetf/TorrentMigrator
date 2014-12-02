#include <gtest-strip.h>
#include "utorrentaccessor.h"

class uTorrentAccessorTest : public ::testing::Test
{
protected:
    uTorrentAccessorTest() {
        ira = new uTorrentAccessor();
    }

    ~uTorrentAccessorTest() {
        delete ira;
    }

    IRecordsAccessor *getAccessor() const { return ira; }

    IRecordsAccessor *getConfigedAccessor() {
        QVariantHash args;
        args["appdata"] = "data/uTorrent/appdata";
        args["extratorrent"] = "data/uTorrent/extra";
        ira->setup(args);
        return ira;
    }

    IRecordsAccessor *ira = nullptr;
};

TEST_F(uTorrentAccessorTest, Setup)
{
    IRecordsAccessor *ira = getAccessor();
    QVariantHash args;
    args["appdata"] = "data/uTorrent/appdata";
    args["extratorrent"] = "data/uTorrent/extra";
    EXPECT_EQ(true, ira->setup(args)) << "setup failed";
}

TEST_F(uTorrentAccessorTest, ReadAll)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    QList<TorrentRecord> list;
    EXPECT_EQ(true, ira->readAll(list)) << "readAll failed";

    EXPECT_EQ(79, list.size());
}

TEST_F(uTorrentAccessorTest, WriteAll)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    QList<TorrentRecord> list;
    EXPECT_EQ(true, ira->writeAll(list)) << "writeAll failed";
}

TEST_F(uTorrentAccessorTest, Add)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    TorrentRecord re;
    EXPECT_EQ(true, ira->add(re)) << "add failed";
}

TEST_F(uTorrentAccessorTest, Update)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    TorrentRecord re;
    EXPECT_EQ(true, ira->update(re)) << "update failed";
}

TEST_F(uTorrentAccessorTest, Remove)
{
    IRecordsAccessor *ira = getConfigedAccessor();

    QString hash("17adf84538492f47de042dc04d087e717c4de45a");
    EXPECT_EQ(true, ira->remove(hash)) << "remove failed";

    QList<TorrentRecord> list;
    ASSERT_EQ(true, ira->readAll(list));
    EXPECT_EQ(78, list.size());
}

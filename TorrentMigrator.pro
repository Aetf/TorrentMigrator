TEMPLATE = subdirs
TARGET = TorrentMigrator
CONFIG += ordered

SUBDIRS = \
    external \
    src \
    app \
    neoui \
    tests
OTHER_FILES += \
    style.astylerc

app.depends = src
neoui.depends = src
tests.depends = src
src.depends = external

# A custom target to directly run tests
runtests.depends = all
unix:runtests.commands = $${OUT_PWD}/tests/runtests.sh
win32:runtests.commands = $${OUT_PWD}/tests/runtests.bat
QMAKE_EXTRA_TARGETS += runtests

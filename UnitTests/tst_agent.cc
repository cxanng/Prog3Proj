#include <QtTest>
#include "agent.h"

class AgentTest: public QObject {
    Q_OBJECT

public:
    AgentTest();
    ~AgentTest();

private Q_SLOTS:
    void testInit();
    void testInit_data();

    void testModifyConnection();
    void testModifyConnection_data();

};

AgentTest::AgentTest() {

}

AgentTest::~AgentTest() {

}

void AgentTest::testInit() {
    QFETCH(QString, name);
    QFETCH(QString, title);
    QFETCH(QString, expectName);
    QFETCH(QString, expectTitle);

    CardModel::Agent agent(name, title);
    QVERIFY2(agent.name() == expectName, "Wrong name");
    QVERIFY2(agent.title() == expectTitle, "Wrong title");
}

void AgentTest::testInit_data() {
    QTest::addColumn<QString>("name");
    QTest::addColumn<QString>("title");
    QTest::addColumn<QString>("expectName");
    QTest::addColumn<QString>("expectTitle");

    QTest::addRow("Empty name")  << "" << "title" << "Default agent name" << "title";
    QTest::addRow("Empty title") << "name" << "" << "name" << "Default agent title";
    QTest::addRow("Both valid")  << "name" << "title" << "name" << "title";
}

void AgentTest::testModifyConnection() {
    QFETCH(unsigned short, init);
    QFETCH(short, change);
    QFETCH(unsigned short, expect);

    CardModel::Agent agent("name", "title");
    agent.setConnections(init);
    agent.modifyConnections(change);
    QVERIFY2(agent.connections() == expect, "Wrong number of connections after modifying");
}

void AgentTest::testModifyConnection_data() {
    QTest::addColumn<unsigned short>("init");
    QTest::addColumn<short>("change");
    QTest::addColumn<unsigned short>("expect");

    QTest::addRow("Normal increment")            << (unsigned short)(10) << short(20) << (unsigned short)(30);
    QTest::addRow("Normal decrement")            << (unsigned short)(30) << short(-10) << (unsigned short)(20);
    QTest::addRow("Decrease more than existing") << (unsigned short)(10) << short(-20) << (unsigned short)(10);

}

QTEST_APPLESS_MAIN(AgentTest)
#include "tst_agent.moc"

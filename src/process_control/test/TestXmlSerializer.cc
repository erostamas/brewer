#include <gmock/gmock.h>
#include <sstream>

#include "ProcessVariable.h"
#include "ProcessVariableStore.h"
#include "XmlSerializer.h"

TEST(TestXmlSerializer, test) {
    ProcessVariable<TYPE::DOUBLE> x("doublevar", Accessibility::READWRITE);
    x = 5.5;
    ProcessVariable<TYPE::STRING> y("stringvar", Accessibility::READWRITE);
    y = "value";
    XmlSerializer serializer;
    std::stringstream ss;
    serializer.serialize(ss);
    std::cout << ss.str() << std::endl;
}

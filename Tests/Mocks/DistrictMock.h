#include <gmock/gmock.h>

#include "District.h"

class DistrictMock : public District {
public:
  MOCK_METHOD1(assignPropertyToDistrict, void(const Estate *));
  MOCK_METHOD1(assignPropertisToDistrict,
               void(const std::vector<const Estate *> &));
  MOCK_CONST_METHOD0(propertis, const std::vector<const Estate *> &());
};

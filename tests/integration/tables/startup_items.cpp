/**
 * Copyright (c) 2014-present, The osquery authors
 *
 * This source code is licensed as defined by the LICENSE file found in the
 * root directory of this source tree.
 *
 * SPDX-License-Identifier: (Apache-2.0 OR GPL-2.0-only)
 */

// Sanity check integration test for startup_items
// Spec file: specs/macwin/startup_items.table

#include <osquery/tests/integration/tables/helper.h>

namespace osquery {
namespace table_tests {

class StartupItemsTest : public testing::Test {
 protected:
  void SetUp() override {
    setUpEnvironment();
  }
};

TEST_F(StartupItemsTest, test_sanity) {
  auto const data = execute_query("select * from startup_items");

  ValidationMap row_map = {
      {"name", NonEmptyString},
      {"path", NonEmptyString},
      {"args", NormalType},
      {"type", SpecificValuesCheck{"Startup Item", "Login Item"}},
      {"source", NonEmptyString},
      {"status", SpecificValuesCheck{"enabled", "disabled"}},
      {"username", NormalType},
  };
  validate_rows(data, row_map);
}

} // namespace table_tests
} // namespace osquery

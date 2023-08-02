// LCOV_EXCL_START
#include <gtest/gtest.h>
// LCOV_EXCL_STOP
#include "../src/include/TaxCalculator.h"

TEST(TaxCalcTestSuite, simpleTaxCalc)
{
    // Arrange
    Transaction *data = new Transaction();
    TaxCalculator *subject = new TaxCalculator(data);
    bool taxChangingNotified = false;
    bool taxRateChangingNotified = false;
    bool netChangingNotified = false;
    bool grossChangingNotified = false;

    subject->Changing.Subscribe([&taxChangingNotified, &netChangingNotified, &taxRateChangingNotified, &grossChangingNotified](tax::NotifyPropertyChangingEventArgs args){
      if (args.name() == "Tax") {
        taxChangingNotified = true;
      }
      if (args.name() == "Net") {
        netChangingNotified = true;
      }
      if (args.name() == "TaxRate") {
        taxRateChangingNotified = true;
      }
      if (args.name() == "Gross") {
        grossChangingNotified = true;
      }
    });

    // Act
    subject->Net = 100.0;
    subject->TaxRate = 0.2;

    // Assert
    EXPECT_EQ((double)subject->Tax, 20.0) << "Tax amount is not correct";
    EXPECT_EQ((double)subject->Gross, 120.0) << "Gross amount is not correct";
    EXPECT_EQ(taxChangingNotified, true) << "Tax notification not found";
    EXPECT_EQ(netChangingNotified, true) << "Net notification not found";
    EXPECT_EQ(taxRateChangingNotified, true) << "Tax code notification not found";
    EXPECT_EQ(grossChangingNotified, true) << "Gross notification not found";

    delete subject;
    delete data;
}

TEST(TaxCalcTestSuite, cancellableUpdate)
{
    // Arrange
    Transaction *data = new Transaction();
    TaxCalculator *subject = new TaxCalculator(data);

    subject->Net = 100.0;
    subject->TaxRate = 0.2;

    EXPECT_EQ((double)subject->Tax, 20.0) << "Tax amount is not correct";
    EXPECT_EQ((double)subject->Gross, 120.0) << "Gross amount is not correct";

    subject->Changing.Subscribe([](tax::NotifyPropertyChangingEventArgs& args){
      EXPECT_EQ(args.cancellable(), true) << "Net changing not marked as cancellable";
      args.cancel();
      EXPECT_EQ(args.cancelled(), true) << "Net cancelled flag not set";
    });

    // Act
    subject->Net = 200.0;

    // Assert
    EXPECT_EQ((double)subject->Tax, 20.0) << "Tax amount should not have changed";
    EXPECT_EQ((double)subject->Gross, 120.0) << "Gross amount should not have changed";

    delete subject;
    delete data;
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
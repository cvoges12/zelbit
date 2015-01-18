#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/test/unit_test.hpp>

#include "util.h"

BOOST_AUTO_TEST_SUITE(getarg_tests)

static void
ResetArgs(const std::string& strArg)
{
    std::vector<std::string> vecArg;
    boost::split(vecArg, strArg, boost::is_space(), boost::token_compress_on);

    // Insert dummy executable name:
    vecArg.insert(vecArg.begin(), "testbitcoin");

    // Convert to char*:
    std::vector<const char*> vecChar;
    BOOST_FOREACH(std::string& s, vecArg)
        vecChar.push_back(s.c_str());

    ParseParameters(vecChar.size(), &vecChar[0]);
}

BOOST_AUTO_TEST_CASE(boolarg)
{
    ResetArgs("-ZLB");
    BOOST_CHECK(GetBoolArg("-ZLB"));
    BOOST_CHECK(GetBoolArg("-ZLB", false));
    BOOST_CHECK(GetBoolArg("-ZLB", true));

    BOOST_CHECK(!GetBoolArg("-fo"));
    BOOST_CHECK(!GetBoolArg("-fo", false));
    BOOST_CHECK(GetBoolArg("-fo", true));

    BOOST_CHECK(!GetBoolArg("-ZLBo"));
    BOOST_CHECK(!GetBoolArg("-ZLBo", false));
    BOOST_CHECK(GetBoolArg("-ZLBo", true));

    ResetArgs("-ZLB=0");
    BOOST_CHECK(!GetBoolArg("-ZLB"));
    BOOST_CHECK(!GetBoolArg("-ZLB", false));
    BOOST_CHECK(!GetBoolArg("-ZLB", true));

    ResetArgs("-ZLB=1");
    BOOST_CHECK(GetBoolArg("-ZLB"));
    BOOST_CHECK(GetBoolArg("-ZLB", false));
    BOOST_CHECK(GetBoolArg("-ZLB", true));

    // New 0.6 feature: auto-map -nosomething to !-something:
    ResetArgs("-noZLB");
    BOOST_CHECK(!GetBoolArg("-ZLB"));
    BOOST_CHECK(!GetBoolArg("-ZLB", false));
    BOOST_CHECK(!GetBoolArg("-ZLB", true));

    ResetArgs("-noZLB=1");
    BOOST_CHECK(!GetBoolArg("-ZLB"));
    BOOST_CHECK(!GetBoolArg("-ZLB", false));
    BOOST_CHECK(!GetBoolArg("-ZLB", true));

    ResetArgs("-ZLB -noZLB");  // -ZLB should win
    BOOST_CHECK(GetBoolArg("-ZLB"));
    BOOST_CHECK(GetBoolArg("-ZLB", false));
    BOOST_CHECK(GetBoolArg("-ZLB", true));

    ResetArgs("-ZLB=1 -noZLB=1");  // -ZLB should win
    BOOST_CHECK(GetBoolArg("-ZLB"));
    BOOST_CHECK(GetBoolArg("-ZLB", false));
    BOOST_CHECK(GetBoolArg("-ZLB", true));

    ResetArgs("-ZLB=0 -noZLB=0");  // -ZLB should win
    BOOST_CHECK(!GetBoolArg("-ZLB"));
    BOOST_CHECK(!GetBoolArg("-ZLB", false));
    BOOST_CHECK(!GetBoolArg("-ZLB", true));

    // New 0.6 feature: treat -- same as -:
    ResetArgs("--ZLB=1");
    BOOST_CHECK(GetBoolArg("-ZLB"));
    BOOST_CHECK(GetBoolArg("-ZLB", false));
    BOOST_CHECK(GetBoolArg("-ZLB", true));

    ResetArgs("--noZLB=1");
    BOOST_CHECK(!GetBoolArg("-ZLB"));
    BOOST_CHECK(!GetBoolArg("-ZLB", false));
    BOOST_CHECK(!GetBoolArg("-ZLB", true));

}

BOOST_AUTO_TEST_CASE(stringarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", "eleven"), "eleven");

    ResetArgs("-ZLB -bar");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", "eleven"), "");

    ResetArgs("-ZLB=");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", ""), "");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", "eleven"), "");

    ResetArgs("-ZLB=11");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", ""), "11");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", "eleven"), "11");

    ResetArgs("-ZLB=eleven");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", ""), "eleven");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", "eleven"), "eleven");

}

BOOST_AUTO_TEST_CASE(intarg)
{
    ResetArgs("");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", 11), 11);
    BOOST_CHECK_EQUAL(GetArg("-ZLB", 0), 0);

    ResetArgs("-ZLB -bar");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", 11), 0);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 0);

    ResetArgs("-ZLB=11 -bar=12");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", 0), 11);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 12);

    ResetArgs("-ZLB=NaN -bar=NotANumber");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", 1), 0);
    BOOST_CHECK_EQUAL(GetArg("-bar", 11), 0);
}

BOOST_AUTO_TEST_CASE(doubledash)
{
    ResetArgs("--ZLB");
    BOOST_CHECK_EQUAL(GetBoolArg("-ZLB"), true);

    ResetArgs("--ZLB=verbose --bar=1");
    BOOST_CHECK_EQUAL(GetArg("-ZLB", ""), "verbose");
    BOOST_CHECK_EQUAL(GetArg("-bar", 0), 1);
}

BOOST_AUTO_TEST_CASE(boolargno)
{
    ResetArgs("-noZLB");
    BOOST_CHECK(!GetBoolArg("-ZLB"));
    BOOST_CHECK(!GetBoolArg("-ZLB", true));
    BOOST_CHECK(!GetBoolArg("-ZLB", false));

    ResetArgs("-noZLB=1");
    BOOST_CHECK(!GetBoolArg("-ZLB"));
    BOOST_CHECK(!GetBoolArg("-ZLB", true));
    BOOST_CHECK(!GetBoolArg("-ZLB", false));

    ResetArgs("-noZLB=0");
    BOOST_CHECK(GetBoolArg("-ZLB"));
    BOOST_CHECK(GetBoolArg("-ZLB", true));
    BOOST_CHECK(GetBoolArg("-ZLB", false));

    ResetArgs("-ZLB --noZLB");
    BOOST_CHECK(GetBoolArg("-ZLB"));

    ResetArgs("-noZLB -ZLB"); // ZLB always wins:
    BOOST_CHECK(GetBoolArg("-ZLB"));
}

BOOST_AUTO_TEST_SUITE_END()

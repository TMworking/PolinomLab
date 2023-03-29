#include <gtest.h>
#include "Polynom.h"

TEST(set1, CAN_CREATE_COPIED_POLYNOM)
{
	Polynomial pol1;
	ASSERT_NO_THROW(Polynomial pol2(pol1));
}

TEST(set1, CAN_COPY_POLYNOM)
{
	Polynomial pol1;
	Polynomial pol2;
	ASSERT_NO_THROW(pol1 = pol2);
}

TEST(set1, COPIED_POLYNOMS_HAVE_DIFFERENT_ADRESSES)
{
	Polynomial pol1;
	Polynomial pol2;
	EXPECT_TRUE(pol1.GetLast() != pol2.GetLast());
	EXPECT_TRUE(pol1.GetStart() != pol2.GetStart());
}

TEST(set1, EMPTY_POLYNOM_HAVE_EQUAL_ADRESSES_ON_START_AND_LAST)
{
	Polynomial pol1;
	EXPECT_TRUE(pol1.GetStart() == pol1.GetLast());
}

TEST(set1, CAN_COPY_ECUAL_POLYNOMs)
{
	Polynomial pol1;
	Polynomial pol2(pol1);
	ASSERT_NO_THROW(pol1 = pol2);
}

TEST(set1, CAN_PUSH_MONOM)
{
	Monom m(3, 131213);
	Polynomial pol;
	ASSERT_NO_THROW(pol.Push(&m));
}

TEST(set1, CANT_PUSH_TOO_BIG_MONOM)
{
	Monom m(3, 211903);
	Polynomial pol;
	ASSERT_ANY_THROW(pol.Push(&m));
}

TEST(set1, CAN_INSERT_MONOM)
{
	Monom m(3, 131213);
	Polynomial pol;
	ASSERT_NO_THROW(pol.Insert(&m));
}

TEST(set1, CANT_INSERT_TOO_BIG_MONOM)
{
	Monom m(3, 211903);
	Polynomial pol;
	ASSERT_ANY_THROW(pol.Insert(&m));
}



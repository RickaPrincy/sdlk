#include <gtest/gtest.h>

#include <sdlk/core/jsx.hpp>

using namespace sdlk;

TEST(JSXParser, ValidTag)
{
	std::string jsx = "<Div id=\"container\"><Button>Click Me</Button></Div>";
	ASSERT_EQ(jsx::extract_tag_name(jsx), "Div");
}

TEST(JSXParser, ValidTagWithAttributes)
{
	std::string jsx = "<Button class=\"primary\">Click</Button>";
	ASSERT_EQ(jsx::extract_tag_name(jsx), "Button");
}

TEST(JSXParser, NoTag)
{
	std::string jsx = "Just some text";
	ASSERT_THROW(jsx::extract_tag_name(jsx), std::runtime_error);
}

TEST(JSXParser, EmptyString)
{
	std::string jsx = "";
	ASSERT_THROW(jsx::extract_tag_name(jsx), std::runtime_error);
}

#include "rules.hpp"
#include "src.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("McKeeman Form validation") {
	auto grammar = mckeeman_grammar();

	auto parser = Parser();
	parser.grammar = &grammar;

	SECTION("Character rule") {
		parser.initial_rule_ = rule(grammar, Name("character"));
		init(parser);
		SECTION("Accepting \" \"") {
			auto ss = InputStream(" ");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"!\"") {
			auto ss = InputStream("!");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"#\"") {
			auto ss = InputStream("#");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"~\"") {
			auto ss = InputStream("~");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Rejecting \"\"\"") {
			auto ss = InputStream("\"");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
	}
	SECTION("Characters rule") {
		parser.initial_rule_ = rule(grammar, Name("characters"));
		init(parser);
		SECTION("Accepting \"a\"") {
			auto ss = InputStream("a");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \" !#~\"") {
			auto ss = InputStream(" !#~");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Rejecting \"a\"\"") {
			auto ss = InputStream("a\"");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
	}
	SECTION("Codepoint rule") {
		parser.initial_rule_ = rule(grammar, Name("codepoint"));
		init(parser);
		SECTION("Accepting \" \"") {
			auto ss = InputStream(" ");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"~\"") {
			auto ss = InputStream("~");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
	}
	SECTION("Exclude rule") {
		parser.initial_rule_ = rule(grammar, Name("exclude"));
		init(parser);
		SECTION("Accepting \"\"") {
			auto ss = InputStream("");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \" - 'a'\"") {
			auto ss = InputStream(" - 'a'");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \" - 'a' - 'b'\"") {
			auto ss = InputStream(" - 'a' - 'b'");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Rejecting \"- 'a'\"") {
			auto ss = InputStream("- 'a'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"  'a'\"") {
			auto ss = InputStream("  'a'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \" -'a'\"") {
			auto ss = InputStream(" -'a'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \" - \"") {
			auto ss = InputStream(" - ");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
	}
	SECTION("Indentation rule") {
		parser.initial_rule_ = rule(grammar, Name("indentation"));
		init(parser);
		SECTION("Accepting \"    \"") {
			auto ss = InputStream("    ");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Rejecting \"   \"") {
			auto ss = InputStream("   ");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"     \"") {
			auto ss = InputStream("     ");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
	}
	SECTION("Item rule") {
		parser.initial_rule_ = rule(grammar, Name("item"));
		init(parser);
		SECTION("Accepting \"name\"") {
			auto ss = InputStream("name");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"\"literal\"\"") {
			auto ss = InputStream("\"literal\"");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
	}
	SECTION("Items rule") {
		parser.initial_rule_ = rule(grammar, Name("items"));
		init(parser);
		SECTION("Accepting \"\"literal_a\"\"") {
			auto ss = InputStream("\"literal_a\"");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"\"literal_a\" name_b\"") {
			auto ss = InputStream("\"literal_a\" name_b");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"name_a\"") {
			auto ss = InputStream("name_a");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"name_a \"literal_b\"\"") {
			auto ss = InputStream("name_a \"literal_b\"");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
	}
	SECTION("Letter rule") {
		parser.initial_rule_ = rule(grammar, Name("letter"));
		init(parser);
		SECTION("Accepting \"A\"") {
			auto ss = InputStream("A");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"Z\"") {
			auto ss = InputStream("Z");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"_\"") {
			auto ss = InputStream("_");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"a\"") {
			auto ss = InputStream("a");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"z\"") {
			auto ss = InputStream("z");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Rejecting \"@\"") {
			auto ss = InputStream("@");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"[\"") {
			auto ss = InputStream("[");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"^\"") {
			auto ss = InputStream("^");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"`\"") {
			auto ss = InputStream("`");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"{\"") {
			auto ss = InputStream("{");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
	}
	SECTION("Literal rule") {
		parser.initial_rule_ = rule(grammar, Name("literal"));
		init(parser);
		SECTION("Accepting \"'a'\"") {
			auto ss = InputStream("'a'");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"'a' . 'z'\"") {
			auto ss = InputStream("'a' . 'z'");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"'a' . 'z' - 'b'\"") {
			auto ss = InputStream("'a' . 'z' - 'b'");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"\"abc\"\"") {
			auto ss = InputStream("\"abc\"");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
	}
	SECTION("Name rule") {
		parser.initial_rule_ = rule(grammar, Name("name"));
		init(parser);
		SECTION("Accepting \"a\"") {
			auto ss = InputStream("a");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"ab\"") {
			auto ss = InputStream("ab");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"azAZ_\"") {
			auto ss = InputStream("azAZ_");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Rejecting \"a@\"") {
			auto ss = InputStream("a@");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
	}
	SECTION("Range rule") {
		parser.initial_rule_ = rule(grammar, Name("range"));
		init(parser);
		SECTION("Accepting \"'a' . 'z'\"") {
			auto ss = InputStream("'a' . 'z'");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Rejecting \" . 'z'\"") {
			auto ss = InputStream(" . 'z'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"'a'. 'z'\"") {
			auto ss = InputStream("'a'. 'z'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"'a'  'z'\"") {
			auto ss = InputStream("'a'  'z'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"'a' .'z'\"") {
			auto ss = InputStream("'a' .'z'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"'a' . \"") {
			auto ss = InputStream("'a' . ");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
	}
	SECTION("Singleton rule") {
		parser.initial_rule_ = rule(grammar, Name("singleton"));
		init(parser);
		SECTION("Accepting \"\'a\'\"") {
			auto ss = InputStream("\'a\'");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Accepting \"\'\'\'\"") {
			auto ss = InputStream("\'\'\'");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Rejecting \"\'aa\'\"") {
			auto ss = InputStream("\'aa\'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"\'\"") {
			auto ss = InputStream("\'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
		SECTION("Rejecting \"\'\'\"") {
			auto ss = InputStream("\'\'");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
	}
	SECTION("Space rule") {
		parser.initial_rule_ = rule(grammar, Name("space"));
		init(parser);

		SECTION("Accepting \" \"") {
			auto ss = InputStream(" ");
			parse(parser, ss);
			REQUIRE(is_accepting(parser));
		}
		SECTION("Rejecting \"!\"") {
			auto ss = InputStream("!");
			parse(parser, ss);
			REQUIRE(!is_accepting(parser));
		}
	}
}

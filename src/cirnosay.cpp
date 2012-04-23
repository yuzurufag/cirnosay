#include <getopt.h>

#include <iostream>
#include <sstream>
#include <iterator>

#include "canvas/border_simple.h"
#include "canvas/compose.h"
#include "canvas/picture.h"
#include "canvas/text.h"
#include "out.h"
#include "palette.h"
#include "picture.h"
#include "utils.h"

struct Config
{
	enum {HELP, PALETTE, SAY, NOTHING} action;
	enum {LEFT, RIGHT} align = LEFT;
	int bg = 7, fg = 0;
	int x = 30, y = 9;
	int width = -1;
	std::wstring text;
	std::string image_file = BUILD_DIR "../pictures/l_Touhoudex_Chibi_Cirno.png";
	std::string palette_file = BUILD_DIR "../pal.png";
};

void show_palette()
{
	std::cout << "\n\n";
	for(int y = 0; y < 4; y++)
	{
		std::cout << "    ";
		for(int x = 0; x < 64; x++)
			std::cout << "\e[48;5;" << x+y*64 << "m ";
		std::cout << "\e[m\n";
	}
	std::cout << "\n\n";
}

void show_help()
{
	std::cout <<
	"Usage: cirnosay [option...] [text]\n"
	"  -i, --image <image>      \n"
	"  -p, --palette <palette>  \n"
	"  -l, --left               \n"
	"  -r, --right              \n"
	"  -s, --shift <x>x<y>      \n"
	"  -w, --width <width>      \n"
	"  -b, --background <color> \n"
	"  -f, --foreground <color> \n"
	"  -P, --show-palette       \n"
	"  -h, --help               \n";
}

Config configure(int argc, char **argv)
{
	Config config;
	while(1)
	{
		int option_index = 0;
		static struct option long_options[] = {
			{"image",          required_argument, 0, 'i'},
			{"palette",        required_argument, 0, 'p'},
			{"left",           no_argument,       0, 'l'},
			{"right",          no_argument,       0, 'r'},
			{"shift",          required_argument, 0, 's'},
			{"width",          required_argument, 0, 'w'},
			{"background",     required_argument, 0, 'b'},
			{"foreground",     required_argument, 0, 'f'},
			{"show-palette",   no_argument,       0, 'P'},
			{"help",           no_argument,       0, 'h'},
			{0, 0, 0, 0}
		};
		int c = getopt_long(argc, argv, "i:p:lrs:w:b:f:Ph", long_options, &option_index);
		if(c == -1)
			break;
		int i = 0;
		#define ARG_ASSERT(x, name) do { \
				if(!(x)) \
				{ \
					std::cerr << argv[0] << ": " << optarg << ": invalid " << name << " argument\n"; \
					config.action = Config::NOTHING; \
					return config; \
				} \
			} while(0)
		#define READ_INT(x, end, name) do { \
				x = 0; \
				int s = optarg[i] == '-'?-1:1; \
				if(optarg[i] == '-') i++; \
				for(; optarg[i] >= '0' && optarg[i] <= '9'; i++) \
					x = x*10 + s*(optarg[i] - '0'); \
				ARG_ASSERT(optarg[i++] == end, name); \
			} while(0)
		switch(c)
		{
			case 'i': config.image_file   = optarg; break;
			case 'p': config.palette_file = optarg; break;
			case 'l': config.align = Config::LEFT;  break;
			case 'r': config.align = Config::RIGHT; break;
			case 's':
				READ_INT(config.x, 'x', "shift");
				READ_INT(config.y,  0,  "shift");
				break;
			case 'w':
				READ_INT(config.width, 0, "width");
				ARG_ASSERT(config.width >= -1, "width");
				break;
			case 'b':
				READ_INT(config.bg, 0, "background");
				ARG_ASSERT(config.bg >= -1 && config.bg < 256, "background");
				break;
			case 'f':
				READ_INT(config.fg, 0, "foreground");
				ARG_ASSERT(config.fg >= -1 && config.fg < 256, "foreground");
				break;
			case 'P':
				config.action = Config::PALETTE;
				return config;
			case 'h':
				config.action = Config::HELP;
				return config;
			default:
				config.action = Config::NOTHING;
				return config;
		}
		#undef ARG_ASSERT
		#undef READ_INT
	}

	if (optind < argc)
		config.text = cirno_say::concat_cstrings(argv + optind);
	else
		config.text = cirno_say::read_stdin();

	config.action = Config::SAY;

	return config;
}

void say(const Config &config)
{
	using namespace cirno_say;

	Palette palette(config.palette_file);
	canvas::Picture picture(config.image_file, palette);
	canvas::Text text_canvas = canvas::Text::from_wstring(config.text);
	canvas::BorderSimple border(&text_canvas, config.fg, config.bg, config.align);
	canvas::Compose result;

	if(config.align == Config::LEFT)
	{
		if(config.text.size())
			result.canvas.push_back({config.x, config.y, &border});
		result.canvas.push_back({0, 0, &picture});
	}
	else
	{
		if(config.text.size())
			result.canvas.push_back({0, config.y, &border});
		result.canvas.push_back({border.x() - picture.x() + config.x, 0, &picture});
	}
	result.setMaxX(config.width);

	std::cout << Out(result).to_s();
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
	Config config = configure(argc, argv);
	switch(config.action)
	{
		case Config::HELP:    show_help();             break;
		case Config::PALETTE: show_palette();          break;
		case Config::SAY:     say(config);             break;
		case Config::NOTHING: break;
	}
}

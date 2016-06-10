#include <getopt.h>

#include <fstream>
#include <iostream>

#include "canvas/border_simple.h"
#include "canvas/compose.h"
#include "canvas/picture.h"
#include "canvas/text.h"
#include "config.h"
#include "findfile.h"
#include "out.h"
#include "palette.h"
#include "utils.h"

struct Config
{
	static const int UNDEFINED = -1;
	enum
	{
		HELP,
		PALETTE,
		SAY,
		LIST,
		NOTHING
	} action;
	enum
	{
		LEFT,
		RIGHT
	} align = LEFT;
	bool mirror = false;
	bool _24bit = false;
	int bg = 39, fg = -1;
	int x = UNDEFINED, y = UNDEFINED;
	int width = -1;
	std::wstring text;
	cirno_say::FindFile image_file = cirno_say::FindFile(
	    DATA_DIR "/pictures/", "png", "Touhoudex_Chibi_Cirno");
	cirno_say::FindFile palette_file =
	    cirno_say::FindFile(DATA_DIR "/palettes/", "png", "xterm");
};

void list(const Config &config)
{
	std::cout << "Images:\n";
	for (auto i : config.image_file.list())
		std::cout << "  " << i << std::endl;
	std::cout << "Palettes:\n";
	for (auto i : config.palette_file.list())
		std::cout << "  " << i << std::endl;
}

void show_palette()
{
	std::cout << "\n\n";
	for (int y = 0; y < 4; y++)
	{
		std::cout << "    ";
		for (int x = 0; x < 64; x++)
			std::cout << "\e[48;5;" << x + y * 64 << "m ";
		std::cout << "\e[m\n";
	}
	std::cout << "\n\n";
}

void show_help()
{
	std::cout <<
	"Usage: cirnosay [option...] [text]\n"
	"  -i, --image <xxx>         use <xxx> as image\n"
	"  -p, --palette <xxx>       use <xxx> as palette\n"
	"  -2, --24bit               use 24-bit color\n"
	"  -l, --left                align left\n"
	"  -r, --right               align right\n"
	"  -m, --mirror              flip image\n"
	"  -s, --shift <x>x<y>       relative position of text balloon\n"
	"  -w, --width <width>       output width\n"
	"  -b, --background <color>  background color of text balloon\n"
	"  -f, --foreground <color>  foreground color of text balloon\n"
	"  -L, --list                list available images/palettes and exit\n"
	"  -P, --show-palette        display palette and exit\n"
	"  -h, --help                display this help and exit\n"
	;
}

Config configure(int argc, char **argv)
{
	Config config;
	try
	{
		config.palette_file = getenv("COLORTERM");
	}
	catch (...)
	{
	}
	while (1)
	{
		int option_index = 0;
		static struct option long_options[] = {
		    {"image",        required_argument, 0, 'i'},
		    {"palette",      required_argument, 0, 'p'},
		    {"24bit",        no_argument,       0, '2'},
		    {"left",         no_argument,       0, 'l'},
		    {"right",        no_argument,       0, 'r'},
		    {"mirror",       no_argument,       0, 'm'},
		    {"shift",        required_argument, 0, 's'},
		    {"width",        required_argument, 0, 'w'},
		    {"background",   required_argument, 0, 'b'},
		    {"foreground",   required_argument, 0, 'f'},
		    {"list",         no_argument,       0, 'L'},
		    {"show-palette", no_argument,       0, 'P'},
		    {"help",         no_argument,       0, 'h'},
		    {0, 0, 0, 0}};
		int c = getopt_long(argc, argv, "i:p:2lrms:w:b:f:PLh", long_options,
		                    &option_index);
		if (c == -1)
			break;
		int i = 0;
		#define ARG_ASSERT(x, name) \
			do \
			{ \
				if (!(x)) \
				{ \
					std::cerr << argv[0] << ": " << optarg << ": invalid " \
					          << name << " argument\n"; \
					config.action = Config::NOTHING; \
					return config; \
				} \
			} while (0)
		#define READ_INT(x, end, name) \
			do \
			{ \
				x = 0; \
				int s = optarg[i] == '-' ? -1 : 1; \
				if (optarg[i] == '-') \
					i++; \
				for (; optarg[i] >= '0' && optarg[i] <= '9'; i++) \
					x = x * 10 + s * (optarg[i] - '0'); \
				ARG_ASSERT(optarg[i++] == end, name); \
			} while (0)
		switch (c)
		{
		case 'i':
			try
			{
				config.image_file = optarg;
			}
			catch (...)
			{
				ARG_ASSERT(false, "image");
			}
			break;
		case 'p':
			try
			{
				config.palette_file = optarg;
			}
			catch (...)
			{
				ARG_ASSERT(false, "palette");
			}
			break;
		case '2': config._24bit = true; break;
		case 'l': config.align = Config::LEFT; break;
		case 'r': config.align = Config::RIGHT; break;
		case 'm': config.mirror = true; break;
		case 's':
			READ_INT(config.x, 'x', "shift");
			READ_INT(config.y, 0, "shift");
			ARG_ASSERT(config.x >= 0 && config.y >= 0, "shift");
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
		case 'L': config.action = Config::LIST; return config;
		case 'P': config.action = Config::PALETTE; return config;
		case 'h': config.action = Config::HELP; return config;
		default: config.action = Config::NOTHING; return config;
		}
		#undef ARG_ASSERT
		#undef READ_INT
	}

	if (config.x == Config::UNDEFINED)
	{
		std::ifstream defaults(DATA_DIR "/defaults", std::ifstream::in);
		std::string value;
		int x, y;
		while (true)
		{
			defaults >> value >> x >> y;
			if (!defaults.good())
				break;
			if (value == config.image_file.get_value())
			{
				config.x = x;
				config.y = y;
				break;
			}
		}
	}

	if (optind < argc)
		config.text = cirno_say::concat_cstrings(argv + optind);
	else
		config.text = cirno_say::read_stdin();

	config.action = Config::SAY;

	return config;
}

void say(Config config)
{
	using namespace cirno_say;
	Palette palette;
	if (config._24bit)
		palette = Palette{"", true};
	else
		palette = Palette{config.palette_file.get_filename(), false};
	canvas::Picture picture(config.image_file.get_filename(), palette,
	                        config.mirror);
	canvas::Text text_canvas = canvas::Text::from_wstring(config.text);
	canvas::BorderSimple border(&text_canvas, config.fg, config.bg,
	                            config.align);
	canvas::Compose result;

	if (config.x == Config::UNDEFINED)
	{
		config.x = picture.x() - 2;
		config.y = picture.y() / 2 - 3;
	}

	if (config.align == Config::LEFT)
	{
		if (config.text.size())
			result.canvas.push_back({config.x, config.y, &border});
		result.canvas.push_back({0, 0, &picture});
	}
	else
	{
		if (config.text.size())
			result.canvas.push_back({0, config.y, &border});
		result.canvas.push_back(
		    {border.x() - picture.x() + config.x, 0, &picture});
	}
	result.setMaxX(config.width);

	std::cout << Out(result).to_s();
}

int main(int argc, char **argv)
{
	setlocale(LC_ALL, "");
	Config config = configure(argc, argv);
	switch (config.action)
	{
	case Config::HELP: show_help(); break;
	case Config::PALETTE: show_palette(); break;
	case Config::LIST: list(config); break;
	case Config::SAY: say(config); break;
	case Config::NOTHING: break;
	}
}

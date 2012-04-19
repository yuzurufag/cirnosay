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
	exit(0);
}

void help()
{
	std::cout <<
	"Usage: cirnosay [option...] [text]\n"
	"  -i, --image <image>      \n"
	"  -p, --palette <palette>  \n"
	"  -l, --left               \n"
	"  -r, --right              \n"
	"  -s, --shift <x>x<y>      \n"
	"  -b, --background <color> \n"
	"  -f, --foreground <color> \n"
	"  -P, --show-palette       \n"
	"  -h, --help               \n";

	exit(0);
}

struct Config
{
	int align = 0;
	int bg = 7, fg = 0;
	int x = 30, y = 9;
	std::string image_file = BUILD_DIR "../pictures/l_Touhoudex_Chibi_Cirno.png";
	std::string palette_file = BUILD_DIR "../pal.png";
};

int main(int argc, char **argv)
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
			{"background",     required_argument, 0, 'b'},
			{"foreground",     required_argument, 0, 'f'},
			{"show-palette",   no_argument,       0, 'P'},
			{"help",           no_argument,       0, 'h'},
			{0, 0, 0, 0}
		};
		int c = getopt_long(argc, argv, "i:p:lrs:b:f:Ph", long_options, &option_index);
		if(c == -1)
			break;
		int i = 0;
		#define READ_INT(x, end) do {\
			x = 0; \
			int s = optarg[i] == '-'?-1:1; \
			if(optarg[i] == '-') i++; \
			for(; optarg[i] >= '0' && optarg[i] <= '9'; i++) \
				x = x*10 + s*(optarg[i] - '0'); \
			if(optarg[i++] != end) \
				help(); \
			} while(0)
		switch(c)
		{
			case 'i':
				config.image_file = optarg;
				break;
			case 'p':
				config.palette_file = optarg;
				break;
			case 'l':
				config.align = 0;
				break;
			case 'r':
				config.align = 1;
				break;
			case 's':
				READ_INT(config.x, 'x');
				READ_INT(config.y, 0);
				break;
			case 'b':
				READ_INT(config.bg, 0);
				break;
			case 'f':
				READ_INT(config.fg, 0);
				break;
			case 'P':
				show_palette();
			case 'h':
				help();
			default:
				help();
		}
		#undef READ_INT
	}
	using namespace cirno_say;
	Palette palette(config.palette_file);

	canvas::Picture picture(config.image_file, palette);

	std::wstring text_str;
	if (optind < argc)
	{
		setlocale(LC_ALL, "");
		std::string s = argv[optind];
		for(int i = optind+1; i < argc; i++)
			s += std::string(" ") + argv[i];
		wchar_t *buf = new wchar_t[ s.size() ];
		size_t num_chars = mbstowcs(buf, s.c_str(), s.size() );
		text_str = std::wstring( buf, num_chars );
		delete[] buf;
	}
	else
	{
		setlocale(LC_ALL, "");
		std::wcin >> std::noskipws;
		std::istream_iterator<wchar_t, wchar_t> it(std::wcin);
		std::istream_iterator<wchar_t, wchar_t> end;
		text_str = std::wstring(it, end);
	}

	canvas::Text text = canvas::Text::from_wstring(text_str);
	canvas::BorderSimple border(&text, config.fg, config.bg, config.align);

	canvas::Compose result;
	if(config.align == 0)
	{
		
		result.canvas.push_back({config.x, config.y, &border});
		result.canvas.push_back({0, 0, &picture});
	}
	else
	{
		result.canvas.push_back({0, config.y, &border});
		result.canvas.push_back({border.x() - picture.x() + config.x, 0, &picture});
	}

	std::cout << Out(result).to_s();
}

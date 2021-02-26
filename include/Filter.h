#ifndef GAME_FILTER_COMPONENT_H__
#define GAME_FILTER_COMPONENT_H__

#define FILTER_ALPHA 55

struct Filter {
	unsigned char r;
	unsigned char g;
	unsigned char b;
};

extern const struct Filter Filter_RED;
extern const struct Filter Filter_GREEN;
extern const struct Filter Filter_BLUE;
extern const struct Filter Filter_ORANGE;
extern const struct Filter Filter_VIOLET;

#endif /* GAME_FILTER_H__ */

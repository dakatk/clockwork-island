#ifndef CLOCKWORKISLAND_FILTER_H__
#define CLOCKWORKISLAND_FILTER_H__

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

#endif /* CLOCKWORKISLAND_FILTER_H__ */

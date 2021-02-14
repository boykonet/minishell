#ifndef LEXIC_H
# define LEXIC_H

int 			lexic(char *line);
int 			lexic_token(char **line, int ident);
int 			spec_symb(int quotes, int ident, char c);

#endif
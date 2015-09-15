/*
 * cvar_tokens.h
 *
 * Simple utilities to manipulate tokens.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#ifndef _CVAR_TOKENS_H
#define _CVAR_TOKENS_H

#define DEFAULT_PARAMETER_DELIMITER	';'
#define DEFAULT_KEY_VALUE_DELIMITER	':'

/* A token holds a key-value pair. */
typedef struct cvar_token {
	char *key;
	char *value;
	int used; /* Non-zero if the token is used */
	struct cvar_token *next;
} cvar_token_t;

/*
 * Return 0 if tokenization was successful, non-zero otherwise. This function
 * does not use strtok (or strtok_r) as we need to point out empty keys.
 */
int tokenize(const char *parameters, const char parameter_delimiter,
		const char key_value_delimiter, cvar_token_t **list_head);

/*
 * Finds a token with a given key. Returns NULL if the token is not found or if
 * list_head or key is NULL.
 */
cvar_token_t *find_token(cvar_token_t *list_head, const char *key);

/*
 * Returns a pointer to the first unused token or NULL if no unused tokens
 * exist.
 */
cvar_token_t *unused_tokens(cvar_token_t *list_head);

/*
 * Free up a list of tokens.
 */

void free_tokens(cvar_token_t *list_head);

#endif /* _CVAR_TOKENS_H */

/*
 * cvar_tokens.c
 *
 * Simple utilities to manipulate tokens.
 *
 * Author: Santhosh Kumar Koundinya (santhosh@fsl.cs.sunysb.edu)
 */

#include <stdio.h>
#include <string.h>
#include "cvar_trace.h"
#include "cvar_tokens.h"

/*
 * Return 0 if tokenization was successful, non-zero otherwise. This function
 * does not use strtok (or strtok_r) as we need to point out empty keys.
 */

int tokenize(const char *parameters, const char parameter_delimiter,
		const char key_value_delimiter, cvar_token_t **list_head)
{
	char *param;
	char *param_start, *param_end;
	char *key_start, *key_end;
	cvar_token_t *lhead, *prev, *curr;
	int more_params;
	int no_value;
	int ret = 0;

	if (!parameters)
		goto out;

	ret = -1;

	lhead = prev = NULL;

	param = strdup(parameters);
	if (!param) {
		cvar_log_error("Out of memory");
		goto cleanup;
	}

	param_start = param;
	more_params = 1;

	while (more_params) {
		param_end = strchr(param_start, parameter_delimiter);
		if (param_end)
			*param_end = '\0';
		else {
			param_end = param_start + strlen(param_start);
			more_params = 0;
		}

		if (param_start != param_end) {
			key_start = param_start;
			key_end = strchr(param_start, key_value_delimiter);
			if (key_end) {
				*key_end = '\0';
				no_value = 0;
			} else {
				key_end = param_end;
				no_value = 1;
			}

			if (key_start == key_end) {
				cvar_log_error("Empty key at position %lu in parameter string "
						"\"%s\"", (key_start - param)/sizeof(char) + 1,
						parameters);
				goto cleanup;
			}


			curr = (cvar_token_t *) malloc(sizeof(cvar_token_t));
			if (!curr) {
				cvar_log_error("Out of memory");
				goto cleanup;
			}

			memset(curr, 0x00, sizeof(cvar_token_t));

			curr->key = strdup(key_start);
			if (!curr->key) {
				cvar_log_error("Out of memory");
				goto cleanup;
			}

			if (!no_value) {
				curr->value = strdup(key_end+1);
				if (!curr->value) {
					cvar_log_error("Out of memory");
					goto cleanup;
				}
			}

			if (!prev)
				lhead = prev = curr;
			else {
				prev->next = curr;
				prev = curr;
			}
		}

		if (more_params)
			param_start = param_end + 1;
	}

	*list_head = lhead;
	ret = 0;

out:
	return ret;

cleanup:
	free_tokens(lhead);
	lhead = NULL;
	goto out;
}

/*
 * Finds a token with a given key. Returns NULL if the token is not found or if
 * list_head or key is NULL.
 */

cvar_token_t *find_token(cvar_token_t *list_head, const char *key)
{
	cvar_token_t *t;

	if (!list_head || !key)
		return NULL;

	for (t = list_head; t != NULL; t = t->next) {
		if (t->key && !strcmp(t->key, key))
			return t;
	}

	return NULL;
}

/*
 * Returns a pointer to the first unused token or NULL if no unused tokens
 * exist.
 */

cvar_token_t *unused_tokens(cvar_token_t *list_head)
{
	cvar_token_t *t;

	for (t = list_head; t != NULL; t = t->next) {
		if (!t->used)
			break;
	}

	return t;
}

static void free_token(cvar_token_t *token)
{
	if (!token)
		return;

	if (token->key)
		free(token->key);
	if (token->value)
		free(token->value);

	free(token);

	return;
}

/*
 * Free up a list of tokens.
 */

void free_tokens(cvar_token_t *list_head)
{
	cvar_token_t *curr;

	if (!list_head)
		return;

	while ((curr = list_head->next) != NULL) {
		list_head->next = curr->next;
		free_token(curr);
	}

	free_token(list_head);

	return;
}

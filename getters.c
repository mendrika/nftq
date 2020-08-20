/* libnftables headers */
#include <nftables/libnftables.h>
#include <rule.h>
#include <string.h>

struct table *get_table_by_name(struct nft_ctx *nft, char *family, char *table_name) {
	struct table *t = NULL;
	list_for_each_entry(t, &nft->cache.list, list) {
		if(!strcmp(t->handle.table.name, table_name) && !strcmp(family2str(t->handle.family), family)) {
			return t;
		}
	}
	return NULL;
}

struct chain *get_chain_by_name(struct table *t, char *chain_name) {
	struct chain *c = NULL;

	list_for_each_entry(c, &t->chains, list) {
		if(!strcmp(c->handle.chain.name, chain_name))
			return c;
	}
	return NULL;
}

struct rule *get_rule_by_comment(struct chain *c, char *comment) {
	struct rule  *r = NULL;

	list_for_each_entry(r, &c->rules, list) {
		if((r->comment != NULL) && (!strcmp(r->comment, comment)))
			return r;
	}				
	return NULL;
}
struct rule *get_rule_by_handle(struct chain *c, uint64_t handle) {
	struct rule  *r = NULL;

	list_for_each_entry(r, &c->rules, list) {
		if(r->handle.handle.id == handle)
			return r;
	}				
	return NULL;
}

/*
	rule -> stmt -> stmt_ops -> stmt_types
*/
struct stmt *get_rule_counter(struct rule *r) {
	struct stmt *s = NULL;
	list_for_each_entry(s, &r->stmts, list) {
		if(s->ops->type ==  STMT_COUNTER)
			return s;	
	}
	return NULL;
}

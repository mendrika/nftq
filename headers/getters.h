/* libnftables headers */
#include <nftables/libnftables.h>
#include <rule.h>

#ifndef GETTERS_H
#define GETTERS_H
	struct table *get_table_by_name(struct nft_ctx *nft, char *family, char *table_name);
	struct chain *get_chain_by_name(struct table *table, char *chain_name);
	struct rule *get_rule_by_comment(struct chain *chain, char *comment);
	struct rule *get_rule_by_handle(struct chain *chain, uint64_t handle);
	struct stmt *get_rule_counter(struct rule *r);
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* libnftables headers */
#include <nftables/libnftables.h>
#include <rule.h>

/* getters functions headers */
#include "headers/getters.h"

#define NFTQ_VERSION "1.0\n"

void print_help() {
	printf("nftq - simple program to query nftables counters - ",NFTQ_VERSION);
	printf("\n- must run as root\n- must follow this arguments order:\n\n   nft <family> <table> <chain> <comment/handle> [str_comment | int_handle_value] < packets/bytes>\n\n");
	printf("NB: comment or handle is used by nftq to identify a rule (if several rules contain the exact same comment, nftq will match the first one it meets)\n");
	printf("example:\nsudo ./nftq  ip filter INPUT comment \"total in\" bytes\n\n");
}

int main(int argc, char *argv[]) {
	char *list_cmd = "list ruleset";

	struct nft_ctx *nft = NULL;
	struct table *table = NULL;
	struct chain *chain = NULL;
	struct rule *rule =NULL;
	struct stmt *counter = NULL;
	
	if(argc != 7) {
		print_help();
		return EXIT_FAILURE;
	}
/***************************************************************************************************/
	/* initializing the nft_ctx - see libnftables library documentation LIBNFTABLES(3) */
	nft = nft_ctx_new(NFT_CTX_DEFAULT);
	
	/* checking if nft_ctx_new() succeeded - if not exit the program */	
	if( nft == NULL )
		return EXIT_FAILURE;
	
	/*
		now let's take a snapshot (if I could call it so) of the ruleset into nft by running "list ruleset"
		In fact, all the information we need (tables, chains, objects, statements) are accessible via the cache member
		of the nft_ctx structure (structure definition available in rule.h)
		NB: if there is a better way, feel free to let me know
	*/
	// nft_ctx_buffer_output() redirects output to buffer (see struct output_ctx in nftables.h), we do not need output, we just need the nft_ctx)
	if(nft_ctx_buffer_output(nft) || nft_run_cmd_from_buffer(nft, list_cmd))
		return EXIT_FAILURE;
/***************************************************************************************************/
	/*
		5 progressive steps to get the bytes/counters (4 to access + 1 to print):
	*/

	// step 1: get the table:
	table = get_table_by_name(nft, argv[1], argv[2]);
	if(table == NULL)
		return EXIT_FAILURE;

	// step 2: get the chain:
	chain = get_chain_by_name(table, argv[3]);
	if(chain == NULL)
		return EXIT_FAILURE;

	// step 3: get the rule:
	if(!strcmp(argv[4], "comment"))
		rule = get_rule_by_comment(chain, argv[5]);
	else if(!strcmp(argv[4], "handle"))
		rule = get_rule_by_handle(chain, atoi(argv[5]));
	else
		return EXIT_FAILURE;
	if(rule == NULL)
		return EXIT_FAILURE;

	// step 4: get the counter:
	counter = get_rule_counter(rule);
	if(counter == NULL)
		return EXIT_FAILURE;
 
	// step 5: print the bytes/packets
	if(!strcmp(argv[6], "packets"))
		printf("%d", counter->counter.packets);
	else if(!strcmp(argv[6], "bytes"))
		printf("%d", counter->counter.bytes);
	else
		return EXIT_FAILURE;

/***************************************************************************************************/
	/*
		never forget to free up the nft_ctx before leaving the program	
	*/
	nft_ctx_free(nft);
	
	return EXIT_SUCCESS;
}

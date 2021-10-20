/******************************************************************************
 * Copyright (C) 2018-2021 aitos.io
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/

#include <time.h>
#include "boatconfig.h"
#include "boatiotsdk.h"
#define TIME_LEN 80
BCHAR str_value[90] = {"file_"};
BCHAR time_buf[TIME_LEN]  = {0};
BCHAR file_hash[33] = {0};

BCHAR *key1 = "time";
BCHAR *key2 = "file_hash";
BCHAR *key3 = "file_name";
const BCHAR * chainmaker_user_sign_key  = "-----BEGIN EC PRIVATE KEY-----\n"
										  "MHcCAQEEIM+5FVFBOHIUeUDH2wOkC4Fn6FnMsLHz0SOTreQKz1bDoAoGCCqGSM49\n"
										  "AwEHoUQDQgAED88H7OwVPitBf2NjCH2ZRM0L9k3csW9nq5qFbyAOSsM+ppi0qrFV\n"
										  "+mcQcGEP4H/VTMxWZCmnVZ7a5d+JQt42OQ==\n"
										  "-----END EC PRIVATE KEY-----\n";


const BCHAR * chainmaker_user_sign_cert = "-----BEGIN CERTIFICATE-----\n"
"MIICaDCCAg6gAwIBAgIDCK2ZMAoGCCqGSM49BAMCMIGKMQswCQYDVQQGEwJDTjEQ\n"
"MA4GA1UECBMHQmVpamluZzEQMA4GA1UEBxMHQmVpamluZzEfMB0GA1UEChMWd3gt\n"
"b3JnMS5jaGFpbm1ha2VyLm9yZzESMBAGA1UECxMJcm9vdC1jZXJ0MSIwIAYDVQQD\n"
"ExljYS53eC1vcmcxLmNoYWlubWFrZXIub3JnMB4XDTIxMTEwNzE1MzE0NloXDTI2\n"
"MTEwNjE1MzE0NlowgZExCzAJBgNVBAYTAkNOMRAwDgYDVQQIEwdCZWlqaW5nMRAw\n"
"DgYDVQQHEwdCZWlqaW5nMR8wHQYDVQQKExZ3eC1vcmcxLmNoYWlubWFrZXIub3Jn\n"
"MQ8wDQYDVQQLEwZjbGllbnQxLDAqBgNVBAMTI2NsaWVudDEuc2lnbi53eC1vcmcx\n"
"LmNoYWlubWFrZXIub3JnMFkwEwYHKoZIzj0CAQYIKoZIzj0DAQcDQgAE5lSVTF90\n"
"J60bc8U2MNyYzmS1f7Ez1jOUXNXrakbHU6ZRWmZpAswbmhWkOfpEWBoegtGdPgIe\n"
"IJX8z8KT7RL1YaNaMFgwKQYDVR0OBCIEIP4DgiyLenX5yCWNDAby3VDxjQ1Cha/R\n"
"f8oU/WORTOagMCsGA1UdIwQkMCKAIKHQDgYZIdDzDcmdr5v7yrR52mzecWHmdaWm\n"
"UVerWnaVMAoGCCqGSM49BAMCA0gAMEUCIEneyi79s4M5VjZ6gw4jxHhs8M5h3QAn\n"
"PndVTWzaoaVHAiEAvVmqpu11y7jYpgflziCtU80ujlLs8XHDqSet+l+5oiw=\n"
"-----END CERTIFICATE-----\n";


const BCHAR * chainmaker_root_ca_cert =  "-----BEGIN CERTIFICATE-----\n"
										 "MIICrzCCAlWgAwIBAgIDDsPeMAoGCCqGSM49BAMCMIGKMQswCQYDVQQGEwJDTjEQ\n"
										 "MA4GA1UECBMHQmVpamluZzEQMA4GA1UEBxMHQmVpamluZzEfMB0GA1UEChMWd3gt\n"
										 "b3JnMS5jaGFpbm1ha2VyLm9yZzESMBAGA1UECxMJcm9vdC1jZXJ0MSIwIAYDVQQD\n"
										 "ExljYS53eC1vcmcxLmNoYWlubWFrZXIub3JnMB4XDTIwMTIwODA2NTM0M1oXDTMw\n"
										 "MTIwNjA2NTM0M1owgYoxCzAJBgNVBAYTAkNOMRAwDgYDVQQIEwdCZWlqaW5nMRAw\n"
										 "DgYDVQQHEwdCZWlqaW5nMR8wHQYDVQQKExZ3eC1vcmcxLmNoYWlubWFrZXIub3Jn\n"
										 "MRIwEAYDVQQLEwlyb290LWNlcnQxIjAgBgNVBAMTGWNhLnd4LW9yZzEuY2hhaW5t\n"
										 "YWtlci5vcmcwWTATBgcqhkjOPQIBBggqhkjOPQMBBwNCAAT7NyTIKcjtUVeMn29b\n"
										 "GKeEmwbefZ7g9Uk5GROl+o4k7fiIKNuty1rQHLQUvAvkpxqtlmOpPOZ0Qziu6Hw6\n"
										 "hi19o4GnMIGkMA4GA1UdDwEB/wQEAwIBpjAPBgNVHSUECDAGBgRVHSUAMA8GA1Ud\n"
										 "EwEB/wQFMAMBAf8wKQYDVR0OBCIEIDUkP3EcubfENS6TH3DFczH5dAnC2eD73+wc\n"
										 "UF/bEIlnMEUGA1UdEQQ+MDyCDmNoYWlubWFrZXIub3Jngglsb2NhbGhvc3SCGWNh\n"
										 "Lnd4LW9yZzEuY2hhaW5tYWtlci5vcmeHBH8AAAEwCgYIKoZIzj0EAwIDSAAwRQIg\n"
										 "ar8CSuLl7pA4Iy6ytAMhR0kzy0WWVSElc+koVY6pF5sCIQCDs+vTD/9V1azmbDXX\n"
										 "bjoWeEfXbFJp2X/or9f4UIvMgg==\n"
										 "-----END CERTIFICATE-----\n";


const BCHAR *chainmaker_consensus_url       = "127.0.0.1:12301";
const BCHAR *chainmaker_consensus_hostName  = "chainmaker.org";

BoatChainmakerWalletConfig *g_chaninmaker_wallet_ptr;

void chainmaker_set_node_info(BoatChainmakerNode *node)
{
	int length; 
	node->addr = BoatMalloc(strlen(chainmaker_consensus_url)+1);
	memcpy(node.addr, chainmaker_consensus_url, strlen(chainmaker_consensus_url)+1);

	node->tlsHostName = BoatMalloc(strlen(chainmaker_consensus_hostName)+1);
	memcpy(node.tlsHostName, chainmaker_consensus_hostName, strlen(chainmaker_consensus_hostName)+1);

	node->useTLS = TRUE;
	node->connCnt = 10;
}
BoatTransactionPara get_invoke_para()
{
	//randrom generate
	BoatFieldMax16B  random_data;
	random_data.field_len = 16;
	BoatRandom(random_data.field, random_data.field_len, NULL);

	get_time_string(time_buf);
	array_to_str(random_data.field ,file_hash, 16);
	
	BoatTransactionPara transaction_para;
	transaction_para.n_parameters = 3;
	transaction_para.parameters = BoatMalloc(transaction_para.n_parameters * sizeof(BoatKeyValuePair));

	transaction_para.parameters[0].key   = key1;
	transaction_para.parameters[0].value = time_buf;
	transaction_para.parameters[1].key   = key2;
	transaction_para.parameters[1].value = file_hash;;
	transaction_para.parameters[2].key   = key3;
	transaction_para.parameters[2].value = strcat(str_value, time_buf);
	
	return transaction_para;
}
__BOATSTATIC BOAT_RESULT chainmakerWalletPrepare(void)
{
	BOAT_RESULT index;

	BoatChainmakerWalletConfig wallet_config = {0};
	//set clinet private key context
	wallet_config.user_pri_key_config.prikey_genMode = BOAT_WALLET_PRIKEY_GENMODE_EXTERNAL_INJECTION;
	wallet_config.user_pri_key_config.prikey_type    = BOAT_WALLET_PRIKEY_TYPE_SECP256R1;
	wallet_config.user_pri_key_config.prikey_format  = BOAT_WALLET_PRIKEY_FORMAT_PKCS;
	wallet_config.user_pri_key_config.prikey_content.field_ptr = (BUINT8 *)chainmaker_user_key;
	wallet_config.user_pri_key_config.prikey_content.field_len = strlen(chainmaker_user_key) + 1; //length contain terminator

	//set clinet cert context
	wallet_config.user_cert_content.length = strlen(chainmaker_user_cert) + 1;
	memcpy(wallet_config.user_cert_content.content, chainmaker_user_cert, wallet_config.user_cert_content.length);

	//set tls key context
	wallet_config.user_sign_pri_key_config.prikey_genMode = BOAT_WALLET_PRIKEY_GENMODE_EXTERNAL_INJECTION;
	wallet_config.user_sign_pri_key_config.prikey_type    = BOAT_WALLET_PRIKEY_TYPE_SECP256R1;
	wallet_config.user_sign_pri_key_config.prikey_format  = BOAT_WALLET_PRIKEY_FORMAT_PKCS;
	wallet_config.user_sign_pri_key_config.prikey_content.field_ptr = (BUINT8 *)chainmaker_user_sign_key;
	wallet_config.user_sign_pri_key_config.prikey_content.field_len = strlen(chainmaker_user_sign_key) + 1; //length contain terminator

	//set tls cert context
	wallet_config.user_sign_cert_content.length = strlen(chainmaker_user_sign_cert) + 1;
	memcpy(wallet_config.user_sign_cert_content.content, chainmaker_user_sign_cert, wallet_config.user_sign_cert_content.length);

	if (strlen(chainmaker_root_ca_cert) < BOAT_HLFABRIC_CERT_MAX_LEN)
	{
		memcpy(wallet_config.roo_ca_cert, chainmaker_root_ca_cert, strlen(chainmaker_root_ca_cert));	
	}
	chainmaker_set_node_info(&wallet_config.node_info);
	
	/* create fabric wallet */
	index = BoatWalletCreate(BOAT_PROTOCOL_CHAINMAKER, NULL, &wallet_config, sizeof(BoatChainmakerWalletConfig));

	if(index == BOAT_ERROR)
	{
		//BoatLog( BOAT_LOG_CRITICAL, "fabricWalletPrepare failed." );
		return BOAT_ERROR;
	}
	g_chaninmaker_wallet_ptr = BoatGetWalletByIndex(index);
	return BOAT_SUCCESS;
}

void get_time_string(char* time_buf)
{
	time_t rawtime;
	struct tm *info;

	time(&rawtime);
	info = localtime(&rawtime);
	strftime(time_buf, TIME_LEN, "%Y-%m-%d %H:%M:%S", info);	
} 
int main(int argc, char *argv[])
{
	BOAT_RESULT       result  = BOAT_SUCCESS;
	
	/* step-1: Boat SDK initialization */
    BoatIotSdkInit();
	
	/* step-2: prepare wallet */
	result = chainmakerWalletPrepare();
	if (result != BOAT_SUCCESS)
	{
		//BoatLog(BOAT_LOG_CRITICAL, "fabricWalletPrepare failed.");
		return -1;
	}
	/* step-3: Chainmaker transaction structure initialization */
	result = BoatHlChainmakerTxInit(g_chaninmaker_wallet_ptr, chain_id, org_id, &tx_ptr);
	if (result != BOAT_SUCCESS)
	{
		return -1;
	}
	
	result = BoatHlchainmakerAddTxParam(&tx_ptr, 6, "time", "6543235", "file_hash", "ab3456df5799b87c77e7f85", "file_name", "name005");
   	if (result != BOAT_SUCCESS)
	{
		BoatLog(BOAT_LOG_CRITICAL, "BoatHlchainmakerAddTxParam() failed.");
		return -1;
	}
		/* step-4: set transaction 'invoke' command */
	result = BoatHlchainmakerContractInvoke(&tx_ptr, "save","fact", true, &invoke_reponse); 
	if (result != BOAT_SUCCESS)
	{
		return -1;
	}


result = BoatHlchainmakerContractQuery(&tx_ptr, "find_by_file_hash","fact", &query_reponse);
	if (result != BOAT_SUCCESS)
	{
		return -1;
	}
	
	/* step-6: chainmaker transaction structure Deinitialization */
	BoatHlchainmakerTxDeInit(&tx_ptr);
/* step-7: Boat SDK Deinitialization */
    BoatIotSdkDeInit();
    return 0;
}

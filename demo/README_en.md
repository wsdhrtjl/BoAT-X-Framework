### Compile and Run Demo
#### Ready
SDK provides Demo based on Ethereum, PlatON, PlatONE, FISCO-BCOS, Hyperledger Fabric and HW-BCS. Before running these demos, the corresponding blockchain node software is need to installed(or have known nodes) and deploy the smart contracts required by the demo.  

The smart contract used by the demo and its ABI JSON file are placed in:  

|Demo smart contract                                          |Contract ABI JSON file                                        |use             |
|:----------------------------------------------------------- |:------------------------------------------------------------ |:-------------- |
|\<SDKRoot\>/demo/demo_ethereum/demo_contract/StoreRead.sol   |\<SDKRoot\>/demo/demo_ethereum/demo_contract/StoreRead.json   |Ethereum demo   |
|\<SDKRoot\>/demo/demo_platone/demo_contract/StoreRead.sol    |\<SDKRoot\>/demo/demo_platone/demo_contract/StoreRead.json    |PlatONE demo    |
|\<SDKRoot\>/demo/demo_fiscobcos/demo_contract/HelloWorld.sol |\<SDKRoot\>/demo/demo_fiscobcos/demo_contract/HelloWorld.json |FISCO-BCOS demo |

Before running Ethereum's Demo, you need to install the Ethereum node simulator ganache, as well as the Ethereum smart contract compilation deployment tool truffle, could visit this website: https://truffleframework.com .
	
Ganache has a ganache-cli version of the command line interface, and a Ganache version of the graphical interface. The ganache-cli of the command line interface and the Ganache 1.x version of the graphical interface will not be saved. If the process of ganache-cli or Ganache 1.x is terminated, the deployed contract will be lost. The command truffle migrate - reset Redeploy the contract, the address of the redeployed contract may change. The Ganache 2.x version of the graphical interface can create a Workspace save state. After closing and reopening the Workspace next time, the deployed contract still does not need to be redeployed.  
In addition to using the ganache simulator, you can also use the Ethereum test network such as Ropsten (you need to apply for a free test token).  

Before running the PlatON Demo, the PlatON node need to be installed. The specific process can be referred to this website: https://platon.network/ .  

Before running the PlatONE Demo, you need to install the PlatONE node, as well as smart contract compilation and deployment tools,could visit this website: https://platone.wxblockchain.com .

Before running the FISCO-BCOS Demo, you need to install the FISCO-BCOS node and contract deployment.
FISCO-BCOS source code and installation and deployment steps can visit this website: https://fisco-bcos-documentation.readthedocs.io

After completing the node (or simulator) deployment, you need to follow the instructions on the relevant websites to deploy the Demo smart contract. After the smart contract is successfully deployed, the contract address will be generated.  

The Demo C code that calls the smart contract is placed in:  

|Demo C code                                                 |use                             |
|:---------------------------------------------------------- |:------------------------------ |
|\<SDKRoot\>/demo/demo_ethereum/demo_ethereum_storeread.c    |Ethereum demo use case          |
|\<SDKRoot\>/demo/demo_ethereum/demo_ethereum_transfer.c     |Ethereum transfer demo use case |
|\<SDKRoot\>/demo/demo_platon/demo_platon_transfer.c         |PLATON transfer demo use case   |
|\<SDKRoot\>/demo/demo_platone/demo_platone_mycontract.c     |PLATONE demo use case           |
|\<SDKRoot\>/demo/demo_fiscobcos/demo_fiscobcos_helloworld.c |FISCO-BCOS demo use case        |

Before compiling the Demo, you need to modify the following parts of the Demo C code:  
- For ETHEREUM, PLATON, FISCO-BCOS, PLATONE:  
	1. Search for `demoUrl` and fill in the node URL (including port) as the IP address and RPC port of the actual deployed node or simulator  
	2. If the demo needs to use the native private key, search for `native_demoKey` and set the client private key as:  
		- For ETHEREUM, set it to the private key of any account generated by ganache  
    - For PlatON, there is no need to modify the private key in the Demo  
		- For PlatONE, there is no need to modify the private key in the Demo  
		- For FISCO-BCOS, set it to the native format private key corresponding to the private key under <FISCO-BCOS_ROOT>/console/accounts  
	3. If the demo needs to use the native private key, search for `pkcs_demoKey` and set the client private key as:  
		- For Ethereum, set the PKCS format private key corresponding to the private key of any account generated by Ganache  
    - For PlatONE, there is no need to modify the private key in the Demo
		- For PlatONE, there is no need to modify the private key in the Demo  
		- For FISCO-BCOS, set it to the private key under <FISCO-BCOS_ROOT>/console/accounts  
	4. Search for `demoRecipientAddress` and modify it to the deployment address of the Demo contract.  

- For FABRIC:  
	1. Search for `fabric_client_demokey` and set the private key used by the client  
	2. Search for `fabric_client_democert` and set the certificate corresponding to the client private key  
	3. If TLS is enabled for the demo, search for `fabric_org1_tlsCert`, `fabric_org2_tlsCert`, `fabric_order_tlsCert`, and set the CA certificate chain  
	4. Search for `fabric_demo_order1_url`, `fabric_demo_endorser_peer0Org1_url`, `fabric_demo_endorser_peer1Org1_url`, `fabric_demo_endorser_peer0Org2_url`, `fabric_demo_endorser_peer1Org2_url`, and set the url address of the endorsement node and sorting node  
	5. If TLS is enabled in the demo, search for `fabric_demo_order1_hostName`, `fabric_demo_endorser_peer0Org1_hostName`, `fabric_demo_endorser_peer1Org1_hostName`, `fabric_demo_endorser_peer0Org2_hostName`, `fabric_demo_endorser_peer1Org2_hostName` and set the host name of the node  

- For HW-BCS:  
	1. Search for `hw_bcs_client_demokey` and set the private key used by the client  
	2. Search for `hw_bcs_client_democert` and set the certificate corresponding to the client private key  
	3. If TLS is enabled for the demo, search for `hw_bcs_org1_tlsCert`, `hw_bcs_org2_tlsCert`, and set the CA certificate chain  
	4. Search for `hw_bcs_demo_endorser_peer0Org1_url`, `hw_bcs_demo_endorser_peer0Org2_url`, `hw_bcs_demo_order_url`, and set the url address of the endorsement node and sorting node  
	5. If TLS is enabled in the demo, search for `hw_bcs_demo_endorser_peer0Org1_hostName`, `hw_bcs_demo_endorser_peer0Org2_hostName`, `hw_bcs_demo_order_hostName`and set the host name of the node  

#### Compile Demo
Execute the following commands in the \<SDKRoot\> directory to compile the SDK call Demo:  
````
$make demo
````

The generated Demo programs are located under the path \<SDKRoot\>/build/demo/demo_\<protocol\>/<demo_name>, and the <protocol> can be `ethereum` `platon` `fisco-bcos` `platone` `fabric` `hwbcs`.

### Trouble Shooting in Compilation
1.  A message similar to "Makefile: 120: *** missing delimiter. Stop" is prompted during compilation.  
This problem is generally caused by the command under target in the Makefile that does not start with Tab (ASCII code 0x09). Note that when you press the Tab key, the text editor may replace the Tab character with a number of spaces. The text editor should be set not to replace Tab with spaces.

2. The prompt "curl/curl.h" cannot be found during compilation  
This problem is caused by the fact that curl and its development files are not installed in the system. For Host compilation on a Linux distribution, please note that only installing the curl package is not enough, you also need to install its development file package. The development file package has different names in different Linux distributions, usually named similar to curl-devel, or libcurl. For details, please refer to the package management tool of the Linux distribution you are using.    

If curl is compiled with source code and is not installed in the system directory, you should specify its search path in external.env, and specify the path where the curl library is located when linking.  

In cross-compilation, pay special attention to the search path and library should point to the header files and libraries in the cross-compilation environment, and should not point to the path on the Host that executes the compilation.

3. When cross-compiling and linking, it prompts that the byte order, bit width or ELF format does not match  
This problem is usually because in cross-compilation, some libraries refer to the Host library, and the Obj file is generated by cross-compilation, or some libraries are 32-bit and the other is 64-bit. You should carefully check the paths of all libraries to avoid mixed links between Host and Target libraries, or libraries with different bit widths.  

You can use the following command to check whether the library file is the ARM version or the x86 version, and the bit width:  
$file \<lib or obj file name\>

4. The compilation prompts that the executable file could not be found, or that the parameters are incorrect  
Common tips:  
'make' is not an internal or external command, nor is it an executable program or batch file.  
mkdir… command syntax is incorrect.  
FIND: The parameter format is incorrect  

This problem is generally caused by compiling under Windows, but Cygwin is not installed, or the paths of BOAT_RM, BOAT_MKDIR, and BOAT_FIND are not correctly configured in the Makefile. Please refer to section [Use Windows as Compiler Environment](#Use-Windows-as-Compiler-Environment) to install Cygwin and configure Makefile.


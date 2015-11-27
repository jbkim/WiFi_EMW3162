#ifndef __HOMEKITPAIRPROTOCOL_h__
#define __HOMEKITPAIRPROTOCOL_h__

#include "Common.h"
#include "HTTPUtils.h"
#include "MICODefine.h"
#include "MICOSRPServer.h"
#include "HomeKitHTTPUtils.h"



/*Pair setup info*/
typedef struct _pairInfo_t {
  char              *SRPUser;
  srp_server_t      *SRPServer;
  uint8_t           *SRPControllerPublicKey;
  ssize_t           SRPControllerPublicKeyLen;
  uint8_t           *SRPControllerProof;
  ssize_t           SRPControllerProofLen;
  uint8_t           *HKDF_Key;
  bool              pairListFull;
} pairInfo_t;


/*Pair verify info*/
typedef struct _pairVerifyInfo_t {
  bool                      verifySuccess;
  int                       haPairVerifyState;
  uint8_t                   *pControllerLTPK;
  char                      *pControllerIdentifier;
  uint8_t                   *pControllerCurve25519PK;
  uint8_t                   *pAccessoryCurve25519PK;
  uint8_t                   *pAccessoryCurve25519SK;
  uint8_t                   *pSharedSecret;
  uint8_t                   *pHKDFKey;
  uint8_t                   *A2CKey;
  uint8_t                   *C2AKey;
} pairVerifyInfo_t;

void HKSetPassword (const uint8_t * password, const size_t passwordLen);

void HKSetVerifier (const uint8_t * verifier, const size_t verifierLen, const uint8_t * salt, const size_t saltLen );

void HKCleanPairSetupInfo(pairInfo_t **info, mico_Context_t * const inContext);

pairVerifyInfo_t* HKCreatePairVerifyInfo(void);

void HKCleanPairVerifyInfo(pairVerifyInfo_t **verifyInfo);

OSStatus HKPairSetupEngine( int inFd, HTTPHeader_t* inHeader, pairInfo_t** inInfo, mico_Context_t * const inContext );

OSStatus HKPairVerifyEngine( int inFd, HTTPHeader_t* inHeader, pairVerifyInfo_t* inInfo, mico_Context_t * const inContext );

OSStatus HKPairAddRemoveEngine( int inFd, HTTPHeader_t* inHeader, security_session_t *session );


#endif


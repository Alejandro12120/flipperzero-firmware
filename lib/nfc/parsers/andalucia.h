#pragma once

#include "nfc_supported_card.h"

bool andalucia_parser_verify(NfcWorker* nfc_worker, FuriHalNfcTxRxContext* tx_rx);

bool andalucia_parser_read(NfcWorker* nfc_worker, FuriHalNfcTxRxContext* tx_rx);

bool andalucia_parser_parse(NfcDeviceData* dev_data);

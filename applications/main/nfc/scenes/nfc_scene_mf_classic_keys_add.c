#include "../nfc_i.h"
#include <dolphin/dolphin.h>

void nfc_scene_mf_classic_keys_add_byte_input_callback(void* context) {
    Nfc* nfc = context;

    view_dispatcher_send_custom_event(nfc->view_dispatcher, NfcCustomEventByteInputDone);
}

void nfc_scene_mf_classic_keys_add_on_enter(void* context) {
    Nfc* nfc = context;

    // Setup view
    ByteInput* byte_input = nfc->byte_input;
    byte_input_set_header_text(byte_input, "Enter the key in hex");
    byte_input_set_result_callback(
        byte_input,
        nfc_scene_mf_classic_keys_add_byte_input_callback,
        NULL,
        nfc,
        nfc->byte_input_store,
        6);
    view_dispatcher_switch_to_view(nfc->view_dispatcher, NfcViewByteInput);
}

bool nfc_scene_mf_classic_keys_add_on_event(void* context, SceneManagerEvent event) {
    Nfc* nfc = context;
    bool consumed = false;

    if(event.type == SceneManagerEventTypeCustom) {
        if(event.event == NfcCustomEventByteInputDone) {
            // Add key to dict
            // bool key_added = false;
            MfClassicDict* userDict = mf_classic_dict_alloc(MfClassicDictTypeUser);
            MfClassicDict* flipperDict = mf_classic_dict_alloc(MfClassicDictTypeSystem);

            if(userDict && flipperDict) {
                if(mf_classic_dict_is_key_present(userDict, nfc->byte_input_store) ||
                   mf_classic_dict_is_key_present(flipperDict, nfc->byte_input_store)) {
                    scene_manager_next_scene(
                        nfc->scene_manager, NfcSceneMfClassicKeysWarnDuplicate);
                } else if(mf_classic_dict_add_key(userDict, nfc->byte_input_store)) {
                    scene_manager_set_scene_state(
                        nfc->scene_manager, NfcSceneSaveSuccess, NfcSceneMfClassicKeys);
                    scene_manager_next_scene(nfc->scene_manager, NfcSceneSaveSuccess);
                    dolphin_deed(DolphinDeedNfcMfcAdd);
                } else {
                    scene_manager_set_scene_state(
                        nfc->scene_manager, NfcSceneDictNotFound, NfcSceneMfClassicKeys);
                    scene_manager_next_scene(nfc->scene_manager, NfcSceneDictNotFound);
                }
            } else {
                scene_manager_set_scene_state(
                    nfc->scene_manager, NfcSceneDictNotFound, NfcSceneMfClassicKeys);
                scene_manager_next_scene(nfc->scene_manager, NfcSceneDictNotFound);
            }
            mf_classic_dict_free(userDict);
            mf_classic_dict_free(flipperDict);
            consumed = true;
        }
    }
    return consumed;
}

void nfc_scene_mf_classic_keys_add_on_exit(void* context) {
    Nfc* nfc = context;

    // Clear view
    byte_input_set_result_callback(nfc->byte_input, NULL, NULL, NULL, NULL, 0);
    byte_input_set_header_text(nfc->byte_input, "");
}

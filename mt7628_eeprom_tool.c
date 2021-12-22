#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#pragma pack(1)
typedef struct {
    uint16_t  chipid;
    uint16_t  revision;

    uint8_t   mac1[6];
    uint8_t   reserved0[30];
    uint8_t   mac2[6];
    uint8_t   mac3[6];

    uint16_t  nic_config0;
    uint16_t  nic_config1;

    uint8_t   reserved1;
    uint8_t   country_reg;
    uint8_t   reserved2;
    uint8_t   led_mode;

    uint16_t  reserved3[3];
    uint16_t  nic_config2;
    uint16_t  reserved4;

    uint16_t  rssi_ofst;
    uint16_t  reserved5[4];
    uint8_t   tx_power_delta;
    uint8_t   reserved6[4];
    uint8_t   temp_sen_cal;
    uint8_t   tx0_pa_tssi_lsb;
    uint8_t   tx0_pa_tssi_msb;
    uint8_t   tx0_power;
    uint8_t   tx0_pwr_ofst_l;
    uint8_t   tx0_pwr_ofst_m;
    uint8_t   tx0_pwr_ofst_h;
    uint8_t   tx1_pa_tssi_lsb;
    uint8_t   tx1_pa_tssi_msb;
    uint8_t   tx1_power;
    uint8_t   tx1_pwr_ofst_l;
    uint8_t   tx1_pwr_ofst_m;
    uint8_t   tx1_pwr_ofst_h;
    uint8_t   reserved7[62];
    uint8_t   tx_pwr_cck_0;
    uint8_t   tx_pwr_cck_1;
    uint8_t   tx_pwr_ofdm_0;
    uint8_t   tx_pwr_ofdm_1;
    uint8_t   tx_pwr_ofdm_2;
    uint8_t   tx_pwr_ofdm_3;
    uint8_t   tx_pwr_ofdm_4;
    uint8_t   tx_pwr_ht_mcs_0;
    uint8_t   tx_pwr_ht_mcs_1;
    uint8_t   tx_pwr_ht_mcs_2;
    uint8_t   tx_pwr_ht_mcs_3;
    uint8_t   tx_pwr_ht_mcs_4;
    uint8_t   tx_pwr_ht_mcs_5;
    uint8_t   tx_pwr_ht_mcs_6;
    uint8_t   reserved8[18];
    uint8_t   ext_lna_rx_gain;
    uint8_t   ext_lna_rx_nf;
    uint8_t   ext_lna_rx_p1db;
    uint8_t   ext_lna_bp_gain0;
    uint8_t   ext_lna_bp_gain1;
    uint8_t   reserved9;
    uint8_t   step_num_neg7;
    uint8_t   step_num_neg6;
    uint8_t   step_num_neg5;
    uint8_t   step_num_neg4;
    uint8_t   step_num_neg3;
    uint8_t   step_num_neg2;
    uint8_t   step_num_neg1;
    uint8_t   step_num_neg0;
    uint8_t   step_num_ref;
    uint8_t   step_num_temp;
    uint8_t   step_num_pos_1;
    uint8_t   step_num_pos_2;
    uint8_t   step_num_pos_3;
    uint8_t   step_num_pos_4;
    uint8_t   step_num_pos_5;
    uint8_t   step_num_pos_6;
    uint8_t   step_num_pos_7;
    uint8_t   reserved10[29];
    uint8_t   xtal_cal;
    uint8_t   xtal_trim2;
    uint8_t   xtal_trim3;
} MT7620_EEPROM;
#pragma pack()

void mt7620_eeprom_load(MT7620_EEPROM *eeprom, char *file)
{
    FILE *fp = fopen(file, "rb");
    if (fp) {
        fread(eeprom, 1, sizeof(MT7620_EEPROM), fp);
        fclose(fp);
    }
}

void mt7620_eeprom_save(MT7620_EEPROM *eeprom, char *file)
{
    FILE *fp = fopen(file, "wb");
    if (fp) {
        fwrite(eeprom, 1, sizeof(MT7620_EEPROM), fp);
        fclose(fp);
    }
}

void mt7620_eeprom_print(MT7620_EEPROM *eeprom)
{
    printf("chipid  : %04X\n", eeprom->chipid  );
    printf("revision: %04X\n", eeprom->revision);
    printf("mac1    : %02X:%02X:%02X:%02X:%02X:%02X\n", eeprom->mac1[0], eeprom->mac1[1], eeprom->mac1[2], eeprom->mac1[3], eeprom->mac1[4], eeprom->mac1[5]);
    printf("mac2    : %02X:%02X:%02X:%02X:%02X:%02X\n", eeprom->mac2[0], eeprom->mac2[1], eeprom->mac2[2], eeprom->mac2[3], eeprom->mac2[4], eeprom->mac2[5]);
    printf("mac3    : %02X:%02X:%02X:%02X:%02X:%02X\n", eeprom->mac1[0], eeprom->mac3[1], eeprom->mac3[2], eeprom->mac3[3], eeprom->mac3[4], eeprom->mac3[5]);
    printf("\n");

    printf("nic_config0:\n");
    printf("  - EXT_PA_ANTSEL: %d\n"  , (eeprom->nic_config0 >> 14) & 0x3);
    printf("  - BOARD_TYPE   : %d\n"  , (eeprom->nic_config0 >> 12) & 0x3);
    printf("  - EXT_PA_DRV   : %dmA\n", (eeprom->nic_config0 & (1 << 10)) ? 8 : 16);
    printf("  - EXT_2P4G_PA  : %s\n"  , (eeprom->nic_config0 & (1 << 9 )) ? "enable" : "disable");
    printf("  - EXT_5G_PA    : %s\n"  , (eeprom->nic_config0 & (1 << 8 )) ? "enable" : "disable");
    printf("  - TX_PATH      : %d\n"  , (eeprom->nic_config0 >> 4) & 0xF);
    printf("  - RX_PATH      : %d\n"  , (eeprom->nic_config0 >> 0) & 0xF);
    printf("nic_config1:\n");
    printf("  - DAC_TEST     : %d\n"  , (eeprom->nic_config1 >> 15) & 0x1);
    printf("  - TSSI_COMP    : %s\n"  , (eeprom->nic_config1 & (1 << 13)) ? "enable" : "disable");
    printf("  - ANT_DIV_CTRL : %d\n"  , (eeprom->nic_config1 >> 11) & 0x3);
    printf("  - BW_40M_2P4G  : %s\n"  , (eeprom->nic_config1 & (1 << 8 )) ? "enable" : "disable");
    printf("  - WPS          : %s\n"  , (eeprom->nic_config1 & (1 << 7 )) ? "enable" : "disable");
    printf("  - WF1_AUX      : %d\n"  , (eeprom->nic_config1 >> 3) & 0x1);
    printf("  - WF0_AUX      : %d\n"  , (eeprom->nic_config1 >> 2) & 0x1);
    printf("  - TX_POWER     : %s\n"  , (eeprom->nic_config1 & (1 << 1 )) ? "enable" : "disable");
    printf("  - HW_RADIO     : %s\n"  , (eeprom->nic_config1 & (1 << 0 )) ? "enable" : "disable");
    printf("nic_config2:\n");
    printf("  - TEMP_COMP    : %s\n"  , (eeprom->nic_config2 & (1 << 11)) ? "disable": "enable" );
    printf("  - XTAL_OPT     : %d\n"  , (eeprom->nic_config2 >> 9) & 0x3);
    printf("  - ANT_DIV      : %s\n"  , (eeprom->nic_config2 & (1 << 8 )) ? "enable" : "disable");
    printf("  - TX_STREAM    : %d\n"  , (eeprom->nic_config2 >> 4) & 0xF);
    printf("  - RX_STREAM    : %d\n"  , (eeprom->nic_config2 >> 0) & 0xF);
    printf("\n");

    printf("country_reg: %02X\n", eeprom->country_reg);
    printf("led_mode   : %02X\n", eeprom->led_mode  );
    printf("rssi1_ofst : %d\n"  , (eeprom->rssi_ofst >> 8) & 0xFF);
    printf("rssi0_ofst : %d\n"  , (eeprom->rssi_ofst >> 0) & 0xFF);

    printf("tx_power_delta:\n");
    printf("  - DELTA_EN : %s\n", (eeprom->tx_power_delta & (1 << 7)) ? "enable" : "disable");
    printf("  - DELTA_INC: %s\n", (eeprom->tx_power_delta & (1 << 6)) ? "enable" : "disable");
    printf("  - DELTA    : %d\n", (eeprom->tx_power_delta >> 0) & 0x3F);
    printf("temp_sen_cal:\n");
    printf("  - TEMP_COMP_EN: %s\n", (eeprom->temp_sen_cal & (1 << 7)) ? "enable" : "disable");
    printf("  - THADC_SLOP  : %d\n", (eeprom->temp_sen_cal >> 0) & 0x7F);
    printf("\n");

    printf("tx0_pa_tssi: %02X %02X\n", eeprom->tx0_pa_tssi_lsb, eeprom->tx0_pa_tssi_msb);
    printf("  - TX0_PA_TSSI_OFST : %d\n", ((eeprom->tx0_pa_tssi_lsb >> 4) & 0xF) | (eeprom->tx0_pa_tssi_msb << 4));
    printf("  - TX0_PA_TSSI_SLOP : %d\n", ((eeprom->tx0_pa_tssi_lsb >> 0) & 0xF));
    printf("tx0_power  : %d\n", eeprom->tx0_power);
    printf("tx0_pwr_ofst_l:\n");
    printf("  - TX0_TX_PWR_EN    : %s\n", (eeprom->tx0_pwr_ofst_l & (1 << 7)) ? "enable" : "disable");
    printf("  - TX0_TX_PWR_INC   : %s\n", (eeprom->tx0_pwr_ofst_l & (1 << 6)) ? "enable" : "disable");
    printf("  - TX0_TX_PWR_OFST_L: %d\n", (eeprom->tx0_pwr_ofst_l & 0x3F));
    printf("tx0_pwr_ofst_m:\n");
    printf("  - TX0_TX_PWR_EN    : %s\n", (eeprom->tx0_pwr_ofst_m & (1 << 7)) ? "enable" : "disable");
    printf("  - TX0_TX_PWR_INC   : %s\n", (eeprom->tx0_pwr_ofst_m & (1 << 6)) ? "enable" : "disable");
    printf("  - TX0_TX_PWR_OFST_M: %d\n", (eeprom->tx0_pwr_ofst_m & 0x3F));
    printf("tx0_pwr_ofst_h:\n");
    printf("  - TX0_TX_PWR_EN    : %s\n", (eeprom->tx0_pwr_ofst_h & (1 << 7)) ? "enable" : "disable");
    printf("  - TX0_TX_PWR_INC   : %s\n", (eeprom->tx0_pwr_ofst_h & (1 << 6)) ? "enable" : "disable");
    printf("  - TX0_TX_PWR_OFST_H: %d\n", (eeprom->tx0_pwr_ofst_h & 0x3F));

    printf("tx1_pa_tssi: %02X %02X\n", eeprom->tx1_pa_tssi_lsb, eeprom->tx1_pa_tssi_msb);
    printf("  - TX1_PA_TSSI_OFST : %d\n", ((eeprom->tx1_pa_tssi_lsb >> 4) & 0xF) | (eeprom->tx1_pa_tssi_msb << 4));
    printf("  - TX1_PA_TSSI_SLOP : %d\n", ((eeprom->tx1_pa_tssi_lsb >> 1) & 0xF));
    printf("tx1_power  : %d\n", eeprom->tx1_power);
    printf("tx1_pwr_ofst_l:\n");
    printf("  - TX1_TX_PWR_EN    : %s\n", (eeprom->tx1_pwr_ofst_l & (1 << 7)) ? "enable" : "disable");
    printf("  - TX1_TX_PWR_INC   : %s\n", (eeprom->tx1_pwr_ofst_l & (1 << 6)) ? "enable" : "disable");
    printf("  - TX1_TX_PWR_OFST_L: %d\n", (eeprom->tx1_pwr_ofst_l & 0x3F));
    printf("tx1_pwr_ofst_m:\n");
    printf("  - TX1_TX_PWR_EN    : %s\n", (eeprom->tx1_pwr_ofst_m & (1 << 7)) ? "enable" : "disable");
    printf("  - TX1_TX_PWR_INC   : %s\n", (eeprom->tx1_pwr_ofst_m & (1 << 6)) ? "enable" : "disable");
    printf("  - TX1_TX_PWR_OFST_M: %d\n", (eeprom->tx1_pwr_ofst_m & 0x3F));
    printf("tx1_pwr_ofst_h:\n");
    printf("  - TX1_TX_PWR_EN    : %s\n", (eeprom->tx1_pwr_ofst_h & (1 << 7)) ? "enable" : "disable");
    printf("  - TX1_TX_PWR_INC   : %s\n", (eeprom->tx1_pwr_ofst_h & (1 << 6)) ? "enable" : "disable");
    printf("  - TX1_TX_PWR_OFST_H: %d\n", (eeprom->tx1_pwr_ofst_h & 0x3F));
    printf("\n");

    printf("tx_pwr_cck_0: %02X\n", eeprom->tx_pwr_cck_0);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_cck_0 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_cck_0 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_cck_0 & 0x3F));

    printf("tx_pwr_cck_1: %02X\n", eeprom->tx_pwr_cck_1);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_cck_1 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_cck_1 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_cck_1 & 0x3F));

    printf("tx_pwr_ofdm_0: %02X\n", eeprom->tx_pwr_ofdm_0);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ofdm_0 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ofdm_0 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ofdm_0 & 0x3F));

    printf("tx_pwr_ofdm_1: %02X\n", eeprom->tx_pwr_ofdm_1);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ofdm_1 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ofdm_1 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ofdm_1 & 0x3F));

    printf("tx_pwr_ofdm_2: %02X\n", eeprom->tx_pwr_ofdm_2);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ofdm_2 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ofdm_2 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ofdm_2 & 0x3F));

    printf("tx_pwr_ofdm_3: %02X\n", eeprom->tx_pwr_ofdm_3);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ofdm_3 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ofdm_3 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ofdm_3 & 0x3F));

    printf("tx_pwr_ofdm_4: %02X\n", eeprom->tx_pwr_ofdm_4);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ofdm_4 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ofdm_4 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ofdm_4 & 0x3F));

    printf("tx_pwr_ht_mcs_0: %02X\n", eeprom->tx_pwr_ht_mcs_0);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ht_mcs_0 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ht_mcs_0 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ht_mcs_0 & 0x3F));

    printf("tx_pwr_ht_mcs_1: %02X\n", eeprom->tx_pwr_ht_mcs_1);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ht_mcs_1 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ht_mcs_1 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ht_mcs_1 & 0x3F));

    printf("tx_pwr_ht_mcs_2: %02X\n", eeprom->tx_pwr_ht_mcs_2);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ht_mcs_2 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ht_mcs_2 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ht_mcs_2 & 0x3F));

    printf("tx_pwr_ht_mcs_3: %02X\n", eeprom->tx_pwr_ht_mcs_3);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ht_mcs_3 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ht_mcs_3 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ht_mcs_3 & 0x3F));

    printf("tx_pwr_ht_mcs_4: %02X\n", eeprom->tx_pwr_ht_mcs_4);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ht_mcs_4 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ht_mcs_4 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ht_mcs_4 & 0x3F));

    printf("tx_pwr_ht_mcs_5: %02X\n", eeprom->tx_pwr_ht_mcs_5);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ht_mcs_5 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ht_mcs_5 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ht_mcs_5 & 0x3F));

    printf("tx_pwr_ht_mcs_6: %02X\n", eeprom->tx_pwr_ht_mcs_6);
    printf("  - TX_PWR_COMP_EN: %s\n", (eeprom->tx_pwr_ht_mcs_6 & (1 << 7)) ? "enable" : "disable");
    printf("  - TX_PWR_INC    : %s\n", (eeprom->tx_pwr_ht_mcs_6 & (1 << 6)) ? "increase" : "decrease");
    printf("  - TX_PWR_DELTA  : %d\n", (eeprom->tx_pwr_ht_mcs_6 & 0x3F));
    printf("\n");

    printf("ext_lna_rx_gain : %d\n", eeprom->ext_lna_rx_gain );
    printf("ext_lna_rx_nf   : %d\n", eeprom->ext_lna_rx_nf   );
    printf("ext_lna_rx_p1db : %d\n", eeprom->ext_lna_rx_p1db );
    printf("ext_lna_bp_gain0: %d\n", eeprom->ext_lna_bp_gain0);
    printf("ext_lna_bp_gain1: %d\n", eeprom->ext_lna_bp_gain1);

    printf("step_num_neg7   : %d\n", eeprom->step_num_neg7   );
    printf("step_num_neg6   : %d\n", eeprom->step_num_neg6   );
    printf("step_num_neg5   : %d\n", eeprom->step_num_neg5   );
    printf("step_num_neg4   : %d\n", eeprom->step_num_neg4   );
    printf("step_num_neg3   : %d\n", eeprom->step_num_neg3   );
    printf("step_num_neg2   : %d\n", eeprom->step_num_neg2   );
    printf("step_num_neg1   : %d\n", eeprom->step_num_neg1   );
    printf("step_num_neg0   : %d\n", eeprom->step_num_neg0   );
    printf("step_num_ref    : %d\n", eeprom->step_num_ref    );
    printf("step_num_temp   : %d\n", eeprom->step_num_temp   );
    printf("step_num_pos_1  : %d\n", eeprom->step_num_pos_1  );
    printf("step_num_pos_2  : %d\n", eeprom->step_num_pos_2  );
    printf("step_num_pos_3  : %d\n", eeprom->step_num_pos_3  );
    printf("step_num_pos_4  : %d\n", eeprom->step_num_pos_4  );
    printf("step_num_pos_5  : %d\n", eeprom->step_num_pos_5  );
    printf("step_num_pos_6  : %d\n", eeprom->step_num_pos_6  );
    printf("step_num_pos_7  : %d\n", eeprom->step_num_pos_7  );

    printf("xtal_cal        : %d\n", eeprom->xtal_cal        );
    printf("xtal_trim2      : %d\n", eeprom->xtal_trim2      );
    printf("xtal_trim3      : %d\n", eeprom->xtal_trim3      );
}

int main(void)
{
    MT7620_EEPROM eeprom = {};
    printf("sizeof(eeprom): %d\n", (int)sizeof(eeprom));
    mt7620_eeprom_load (&eeprom, "eeprom-template.bin");
    mt7620_eeprom_print(&eeprom);
    mt7620_eeprom_save (&eeprom, "eeprom-output.bin");
    return 0;
}
















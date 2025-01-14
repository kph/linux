



#include "e1000_hw.h"

/*
 * 1000Base-T Control Register
 */
#define MII_GB_CTRL_MS_MAN      (1 << 12) /* Manual Master/Slave mode */
#define MII_GB_CTRL_MS          (1 << 11) /* Master/Slave negotiation mode */
#define MII_GB_CTRL_PT          (1 << 10) /* Port type */
#define MII_GB_CTRL_ADV_1000FD  (1 << 9) /* Advertise 1000Base-T FD */
#define MII_GB_CTRL_ADV_1000HD  (1 << 8) /* Advertise 1000Base-T HD */


#define MII_BCM54XX_ECR         0x10    /* BCM54xx extended control register */
#define MII_BCM54XX_ECR_IM      0x1000  /* Interrupt mask */
#define MII_BCM54XX_ECR_IF      0x0800  /* Interrupt force */
#define MII_BCM54XX_ESR         0x11    /* BCM54xx extended status register */
#define MII_BCM54XX_ESR_IS      0x1000  /* Interrupt status */ 
#define MII_BCM54XX_EXP_DATA    0x15    /* Expansion register data */
#define MII_BCM54XX_EXP_SEL     0x17    /* Expansion register select */
#define MII_BCM54XX_EXP_SEL_SSD 0x0e00  /* Secondary SerDes select */
#define MII_BCM54XX_EXP_SEL_ER  0x0f00  /* Expansion register select */ 
#define MII_BCM54XX_AUX_CTL     0x18    /* Auxiliary control register */
#define MII_BCM54XX_AUX_CTL_ENCODE(val) (((val & 0x7) << 12)|(val & 0x7))
#define MII_BCM54XX_ISR         0x1a    /* BCM54xx interrupt status register */
#define MII_BCM54XX_IMR         0x1b    /* BCM54xx interrupt mask register */
#define MII_BCM54XX_INT_CRCERR  0x0001  /* CRC error */
#define MII_BCM54XX_INT_LINK    0x0002  /* Link status changed */
#define MII_BCM54XX_INT_SPEED   0x0004  /* Link speed change */
#define MII_BCM54XX_INT_DUPLEX  0x0008  /* Duplex mode changed */
#define MII_BCM54XX_INT_LRS     0x0010  /* Local receiver status changed */
#define MII_BCM54XX_INT_RRS     0x0020  /* Remote receiver status changed */
#define MII_BCM54XX_INT_SSERR   0x0040  /* Scrambler synchronization error */
#define MII_BCM54XX_INT_UHCD    0x0080  /* Unsupported HCD negotiated */
#define MII_BCM54XX_INT_NHCD    0x0100  /* No HCD */
#define MII_BCM54XX_INT_NHCDL   0x0200  /* No HCD link */
#define MII_BCM54XX_INT_ANPR    0x0400  /* Auto-negotiation page received */
#define MII_BCM54XX_INT_LC      0x0800  /* All counters below 128 */
#define MII_BCM54XX_INT_HC      0x1000  /* Counter above 32768 */
#define MII_BCM54XX_INT_MDIX    0x2000  /* MDIX status change */
#define MII_BCM54XX_INT_PSERR   0x4000  /* Pair swap error */

/*
 * MII Link Advertisment
 */
#define MII_ANA_ASF             (1 << 0)/* Advertise Selector Field */
#define MII_ANA_HD_10           (1 << 5)/* Half duplex 10Mb/s supported */
#define MII_ANA_FD_10           (1 << 6)/* Full duplex 10Mb/s supported */
#define MII_ANA_HD_100          (1 << 7)/* Half duplex 100Mb/s supported */
#define MII_ANA_FD_100          (1 << 8)/* Full duplex 100Mb/s supported */
#define MII_ANA_T4              (1 << 9)/* T4 */
#define MII_ANA_PAUSE           (1 << 10)/* Pause supported */
#define MII_ANA_ASYM_PAUSE      (1 << 11)/* Asymmetric pause supported */
#define MII_ANA_RF              (1 << 13)/* Remote fault */
#define MII_ANA_NP              (1 << 15)/* Next Page */

#define MII_ANA_ASF_802_3       (1)     /* 802.3 PHY */


#define MII_BCM54XX_SHD         0x1c    /* 0x1c shadow registers */
#define MII_BCM54XX_SHD_WRITE   0x8000
#define MII_BCM54XX_SHD_VAL(x)  ((x & 0x1f) << 10)
#define MII_BCM54XX_SHD_DATA(x) ((x & 0x3ff) << 0)

#define MII_BCM54XX_AUX_STATUS  0x19    /* Auxiliary status */
#define MII_BCM54XX_AUX_STATUS_LINKMODE_MASK 0x0700
#define MII_BCM54XX_AUX_STATUS_LINKMODE_SHIFT 8
#define MII_BCM54XX_SHD_WR_ENCODE(val, data) \
  (MII_BCM54XX_SHD_WRITE | MII_BCM54XX_SHD_VAL(val) | \
   MII_BCM54XX_SHD_DATA(data))

/*
  * AUXILIARY CONTROL SHADOW ACCESS REGISTERS.  (PHY REG 0x18)
  */
#define MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL       0x0000
#define MII_BCM54XX_AUXCTL_ACTL_TX_6DB          0x0400
#define MII_BCM54XX_AUXCTL_ACTL_SMDSP_ENA       0x0800
  
#define MII_BCM54XX_AUXCTL_MISC_WREN    0x8000
#define MII_BCM54XX_AUXCTL_MISC_FORCE_AMDIX     0x0200
#define MII_BCM54XX_AUXCTL_MISC_RDSEL_MISC      0x7000
#define MII_BCM54XX_AUXCTL_SHDWSEL_MISC 0x0007

#define MII_BCM54XX_AUXCTL_SHDWSEL_AUXCTL       0x0000

/*
  * Broadcom LED source encodings.  These are used in BCM5461, BCM5481,
  * BCM5482, and possibly some others.
  */
#define BCM_LED_SRC_LINKSPD1    0x0
#define BCM_LED_SRC_LINKSPD2    0x1
#define BCM_LED_SRC_XMITLED     0x2
#define BCM_LED_SRC_ACTIVITYLED 0x3
#define BCM_LED_SRC_FDXLED      0x4
#define BCM_LED_SRC_SLAVE       0x5
#define BCM_LED_SRC_INTR        0x6
#define BCM_LED_SRC_QUALITY     0x7
#define BCM_LED_SRC_RCVLED      0x8
#define BCM_LED_SRC_MULTICOLOR1 0xa
#define BCM_LED_SRC_OPENSHORT   0xb
#define BCM_LED_SRC_OFF         0xe     /* Tied high */
#define BCM_LED_SRC_ON          0xf     /* Tied low */

 /*
  * BCM54XX: Shadow registers
  * Shadow values go into bits [14:10] of register 0x1c to select a shadow
  * register to access.
  */

#define BCM54XX_SHD_AUTODETECT 0x1e /* 11110: Auto detect Regisrer */
#define BCM54XX_SHD_MODE        0x1f    /* 11111: Mode Control Register */
#define BCM54XX_SHD_MODE_COPPER 1<<7
#define BCM54XX_SHD_MODE_SER 1<<6
 /*
  * EXPANSION SHADOW ACCESS REGISTERS.  (PHY REG 0x15, 0x16, and 0x17)
  */
 #define MII_BCM54XX_EXP_AADJ1CH0                0x001f
 #define  MII_BCM54XX_EXP_AADJ1CH0_SWP_ABCD_OEN  0x0200
 #define  MII_BCM54XX_EXP_AADJ1CH0_SWSEL_THPF    0x0100
 #define MII_BCM54XX_EXP_AADJ1CH3                0x601f
 #define  MII_BCM54XX_EXP_AADJ1CH3_ADCCKADJ      0x0002
 #define MII_BCM54XX_EXP_EXP08                   0x0F08
 #define  MII_BCM54XX_EXP_EXP08_RJCT_2MHZ        0x0001
 #define  MII_BCM54XX_EXP_EXP08_EARLY_DAC_WAKE   0x0200
 #define MII_BCM54XX_EXP_EXP75                   0x0f75
 #define  MII_BCM54XX_EXP_EXP75_VDACCTRL         0x003c
 #define MII_BCM54XX_EXP_EXP96                   0x0f96
 #define  MII_BCM54XX_EXP_EXP96_MYST             0x0010
 #define MII_BCM54XX_EXP_EXP97                   0x0f97
 #define  MII_BCM54XX_EXP_EXP97_MYST             0x0c0c
 
 

 
 /*
  * Indirect register access functions for the 1000BASE-T/100BASE-TX/10BASE-T
  * 0x1c shadow registers.
  */

static int bcmphy_write(struct e1000_hw *hw,u32 reg,u16 regval){

        u32 ret;
        struct e1000_phy_info *phy = &hw->phy;
        ret=phy->ops.write_reg(hw,reg,regval);
        return ret;
}

static u16 bcmphy_read(struct e1000_hw *hw,u32 reg){

        u16 val;
        struct e1000_phy_info *phy = &hw->phy;
        phy->ops.read_reg(hw,reg,&val);
        return val;
}

 
static int bcm54xx_shadow_read(struct e1000_hw *hw, u16 shadow)
{
         bcmphy_write(hw, MII_BCM54XX_SHD, MII_BCM54XX_SHD_VAL(shadow));
         return MII_BCM54XX_SHD_DATA(bcmphy_read(hw, MII_BCM54XX_SHD));
}
 
static int bcm54xx_shadow_write(struct e1000_hw *hw, u16 shadow, u16 val)
 {
         return bcmphy_write(hw, MII_BCM54XX_SHD,
                          MII_BCM54XX_SHD_WRITE |
                          MII_BCM54XX_SHD_VAL(shadow) |
                          MII_BCM54XX_SHD_DATA(val));
 }
 
#if 0
 /* Indirect register access functions for the Expansion Registers */
 static int bcm54xx_exp_read(struct e1000_hw *hw, u8 regnum)
 {
         int val;
 
         val = bcmphy_write(hw, MII_BCM54XX_EXP_SEL, regnum);
         if (val < 0)
                 return val;
 
         val = bcmphy_read(hw, MII_BCM54XX_EXP_DATA);
 
         /* Restore default value.  It's O.K. if this write fails. */
         bcmphy_write(hw, MII_BCM54XX_EXP_SEL, 0);
 
         return val;
 }
 
 static int bcm54xx_exp_write(struct e1000_hw *hw, u16 regnum, u16 val)
 {
         int ret;

         ret = bcmphy_write(hw, MII_BCM54XX_EXP_SEL, regnum);
         if (ret < 0)
                 return ret;
 
         ret = bcmphy_write(hw, MII_BCM54XX_EXP_DATA, val);
 
         /* Restore default value.  It's O.K. if this write fails. */
         bcmphy_write(hw, MII_BCM54XX_EXP_SEL, 0);
 
         return ret;
 }
#endif
 
 static int bcm54xx_auxctl_write(struct e1000_hw *hw, u16 regnum, u16 val)
 {
         return bcmphy_write(hw, MII_BCM54XX_AUX_CTL, regnum | val);
 }
 
static int bcm54xx_config_init(struct e1000_hw *hw)
 {
         int reg, err;
 
         reg = bcmphy_read(hw, MII_BCM54XX_ECR);
         if (reg < 0)
                 return reg;
 
         /* Mask interrupts globally.  */
         reg |= MII_BCM54XX_ECR_IM;
         err = bcmphy_write(hw, MII_BCM54XX_ECR, reg);
         if (err < 0)
                 return err;
 
         /* Unmask events we are interested in.  */
         reg = ~(MII_BCM54XX_INT_DUPLEX |
                 MII_BCM54XX_INT_SPEED |
                 MII_BCM54XX_INT_LINK);
         err = bcmphy_write(hw, MII_BCM54XX_IMR, reg);
         if (err < 0)
                 return err;
  
         return 0;
 }

void bcm54616s_linkup(struct e1000_hw *hw,int speed , int duplex)
{
    u16 regval;

    /* set speed and full duplex*/
    regval=bcmphy_read(hw,PHY_CONTROL);

    regval &= ~(MII_CR_SPEED_SELECT_MSB | MII_CR_SPEED_SELECT_LSB |MII_CR_FULL_DUPLEX);
    switch(speed){
    case SPEED_10:
        regval |=MII_CR_SPEED_10;
        break;
    case SPEED_100:
        regval |=MII_CR_SPEED_100;
        break;
    case SPEED_1000:
    default:
         regval |=MII_CR_SPEED_1000;
        break;
    }
    switch(duplex){
    case FULL_DUPLEX:
        regval |=MII_CR_FULL_DUPLEX;
        break;
    }

    bcmphy_write(hw,PHY_CONTROL,regval);

    #if 0
    /* set Master auto and cap*/
    regval=bcmphy_read(hw,PHY_1000T_CTRL);
    regval &= ~(MII_GB_CTRL_MS_MAN);
    regval |= MII_ANA_ASF_802_3;
    regval |= MII_ANA_HD_10;
    regval |= MII_ANA_HD_100;
    regval |= MII_ANA_FD_10;
    regval |= MII_ANA_FD_100;
    regval |= MII_ANA_ASYM_PAUSE;
    regval |= MII_ANA_PAUSE | MII_ANA_ASYM_PAUSE;
    regval |= MII_ANA_PAUSE;
    bcmphy_write(hw,PHY_1000T_CTRL,regval);

    regval=bcmphy_read(hw,PHY_CONTROL);
    regval |= MII_CR_AUTO_NEG_EN | MII_CR_RESTART_AUTO_NEG;
    bcmphy_write(hw,PHY_CONTROL,regval);    
    #endif
    
    regval=bcmphy_read(hw,PHY_CONTROL);
    regval &=~(MII_CR_ISOLATE);
    bcmphy_write(hw,PHY_CONTROL,regval);
}

int bcm54616_config_init(struct e1000_hw *hw)
 {
    int err, reg;
    u16 regval;
    int i;

    /* reset PHY */
    regval=1<<15;
    bcmphy_write(hw,PHY_CONTROL,regval);

    usleep_range(10000, 11000);

    /* disable Power down and iso */
    regval=bcmphy_read(hw,PHY_CONTROL);
    regval &=~(MII_CR_POWER_DOWN|MII_CR_ISOLATE);
    bcmphy_write(hw,PHY_CONTROL,regval);

    /* disable suport I */
    /*0000 0100 1100 0010 */
    bcm54xx_auxctl_write(hw,0,0x04c2);

    regval=bcmphy_read(hw,MII_BCM54XX_AUX_CTL);

    /* set 1000base-T */
    regval=bcmphy_read(hw,PHY_1000T_CTRL);
    regval |=CR_1000T_FD_CAPS | CR_1000T_REPEATER_DTE;
    bcmphy_write(hw,PHY_1000T_CTRL,regval);

    /* set ctrl  */
    regval= MII_CR_SPEED_1000|MII_CR_FULL_DUPLEX|MII_CR_SPEED_SELECT_MSB;
    bcmphy_write(hw,PHY_CONTROL,regval);


    /* Setup read from auxilary control shadow register 7 */
    bcmphy_write(hw, MII_BCM54XX_AUX_CTL,MII_BCM54XX_AUX_CTL_ENCODE(7));
    
    /* Read Misc Control register */
    reg = (bcmphy_read(hw, MII_BCM54XX_AUX_CTL) & 0x8FFF) | 0x8010;
    bcmphy_write(hw, MII_BCM54XX_AUX_CTL, reg);
        
    /* Enable auto-detect and copper prefer */
    bcm54xx_shadow_write(hw,BCM54XX_SHD_AUTODETECT,0x31);

    err = bcm54xx_config_init(hw);

    /* set link parner */
    regval     = MII_ANA_ASF_802_3;
    regval |= MII_ANA_HD_10;
    regval |= MII_ANA_HD_100;
    regval |= MII_ANA_FD_10;
    regval |= MII_ANA_FD_100;
    regval |= MII_ANA_ASYM_PAUSE;
    regval |= MII_ANA_PAUSE | MII_ANA_ASYM_PAUSE;
    regval |= MII_ANA_PAUSE;
    bcmphy_write(hw, PHY_AUTONEG_ADV, reg);
           
    i=0;
    while (1) {
        regval = bcm54xx_shadow_read(hw,BCM54XX_SHD_MODE);
        if(regval & BCM54XX_SHD_MODE_SER)
            break;
        if (i++ > 500) {
            //printk("SERDES no link %x\n",regval);
            break;
        }
        usleep_range(1000,2000);   /* 1 ms */
    }
    return err;
 }
 

/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : usbd_custom_hid_if.c
  * @version        : v1.0_Cube
  * @brief          : USB Device Custom HID interface file.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "usbd_custom_hid_if.h"

/* USER CODE BEGIN INCLUDE */

/* USER CODE END INCLUDE */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* USER CODE BEGIN PV */
/* Private variables ---------------------------------------------------------*/

/* USER CODE END PV */

/** @addtogroup STM32_USB_OTG_DEVICE_LIBRARY
  * @brief Usb device.
  * @{
  */

/** @addtogroup USBD_CUSTOM_HID
  * @{
  */

/** @defgroup USBD_CUSTOM_HID_Private_TypesDefinitions USBD_CUSTOM_HID_Private_TypesDefinitions
  * @brief Private types.
  * @{
  */

/* USER CODE BEGIN PRIVATE_TYPES */

/* USER CODE END PRIVATE_TYPES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Defines USBD_CUSTOM_HID_Private_Defines
  * @brief Private defines.
  * @{
  */

/* USER CODE BEGIN PRIVATE_DEFINES */

/* USER CODE END PRIVATE_DEFINES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Macros USBD_CUSTOM_HID_Private_Macros
  * @brief Private macros.
  * @{
  */

/* USER CODE BEGIN PRIVATE_MACRO */

/* USER CODE END PRIVATE_MACRO */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_Variables USBD_CUSTOM_HID_Private_Variables
  * @brief Private variables.
  * @{
  */

/** Usb HID report descriptor. */
__ALIGN_BEGIN static uint8_t CUSTOM_HID_ReportDesc_FS[USBD_CUSTOM_HID_REPORT_DESC_SIZE] __ALIGN_END =
{
  /* USER CODE BEGIN 0 */
		 // Keyboard Report Descriptor
		    0x05, 0x01,        // Usage Page (Generic Desktop Controls)
		    0x09, 0x06,        // Usage (Keyboard)
		    0xA1, 0x01,        // Collection (Application)

		    // Modifier Keys (8 bits)
		    0x05, 0x07,        // Usage Page (Keyboard)
		    0x19, 0xE0,        // Usage Minimum (Left Control)
		    0x29, 0xE7,        // Usage Maximum (Right GUI)
		    0x15, 0x00,        // Logical Minimum (0)
		    0x25, 0x01,        // Logical Maximum (1)
		    0x75, 0x01,        // Report Size (1)
		    0x95, 0x08,        // Report Count (8)
		    0x81, 0x02,        // Input (Data, Variable, Absolute) - Modifier keys

		    // Reserved byte (for padding)
		    0x75, 0x08,        // Report Size (8)
		    0x95, 0x01,        // Report Count (1)
		    0x81, 0x01,        // Input (Constant) - Reserved byte

		    // Regular Keys (6 bytes)
		    0x05, 0x07,        // Usage Page (Keyboard)
		    0x19, 0x00,        // Usage Minimum (0)
		    0x29, 0x65,        // Usage Maximum (Keyboard Application)
		    0x15, 0x00,        // Logical Minimum (0)
		    0x25, 0x65,        // Logical Maximum (101)
		    0x75, 0x08,        // Report Size (8)
		    0x95, 0x06,        // Report Count (6)
		    0x81, 0x00,        // Input (Data, Array) - Regular keys

		    0xC0,              // End Collection (Keyboard)

		    // Consumer Control (Media Keys)
		    0x05, 0x0C,        // Usage Page (Consumer Devices)
		    0x09, 0x01,        // Usage (Consumer Control)
		    0xA1, 0x01,        // Collection (Application)
		    0x15, 0x00,        // Logical Minimum (0)
		    0x25, 0x01,        // Logical Maximum (1)
		    0x75, 0x01,        // Report Size (1)
		    0x95, 0x10,        // Report Count (16 bits)
		    0x09, 0xE9,        // Usage (Volume Up)
		    0x09, 0xEA,        // Usage (Volume Down)
		    0x09, 0xE2,        // Usage (Mute)
		    0x09, 0xB5,        // Usage (Next Track)
		    0x09, 0xB6,        // Usage (Previous Track)
		    0x81, 0x02,        // Input (Data, Variable, Absolute) - Media keys
		    0xC0,              // End Collection (Consumer Control)

		    // Mouse Report Descriptor
		    0x05, 0x01,        // Usage Page (Generic Desktop)
		    0x09, 0x02,        // Usage (Mouse)
		    0xA1, 0x01,        // Collection (Application)
		    0x09, 0x01,        // Usage (Pointer)
		    0xA1, 0x00,        // Collection (Physical)

		    // Buttons (3 buttons)
		    0x05, 0x09,        // Usage Page (Button)
		    0x19, 0x01,        // Usage Minimum (Button 1)
		    0x29, 0x03,        // Usage Maximum (Button 3)
		    0x15, 0x00,        // Logical Minimum (0)
		    0x25, 0x01,        // Logical Maximum (1)
		    0x95, 0x03,        // Report Count (3 buttons)
		    0x75, 0x01,        // Report Size (1)
		    0x81, 0x02,        // Input (Data, Variable, Absolute) - Mouse buttons

		    // Padding (5 bits)
		    0x75, 0x05,        // Report Size (5)
		    0x95, 0x01,        // Report Count (1)
		    0x81, 0x01,        // Input (Constant, Array) - Padding

		    // X and Y Movement (2 bytes)
		    0x05, 0x01,        // Usage Page (Generic Desktop)
		    0x09, 0x30,        // Usage (X)
		    0x09, 0x31,        // Usage (Y)
		    0x15, 0x81,        // Logical Minimum (-127)
		    0x25, 0x7F,        // Logical Maximum (127)
		    0x75, 0x08,        // Report Size (8)
		    0x95, 0x02,        // Report Count (2)
		    0x81, 0x06,        // Input (Data, Variable, Relative) - X and Y movement

		    0xC0,              // End Collection (Mouse)
  /* USER CODE END 0 */
  0xC0    /*     END_COLLECTION	             */
};

/* USER CODE BEGIN PRIVATE_VARIABLES */

/* USER CODE END PRIVATE_VARIABLES */

/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Exported_Variables USBD_CUSTOM_HID_Exported_Variables
  * @brief Public variables.
  * @{
  */
extern USBD_HandleTypeDef hUsbDeviceFS;

/* USER CODE BEGIN EXPORTED_VARIABLES */

/* USER CODE END EXPORTED_VARIABLES */
/**
  * @}
  */

/** @defgroup USBD_CUSTOM_HID_Private_FunctionPrototypes USBD_CUSTOM_HID_Private_FunctionPrototypes
  * @brief Private functions declaration.
  * @{
  */

static int8_t CUSTOM_HID_Init_FS(void);
static int8_t CUSTOM_HID_DeInit_FS(void);
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state);

/**
  * @}
  */

USBD_CUSTOM_HID_ItfTypeDef USBD_CustomHID_fops_FS =
{
  CUSTOM_HID_ReportDesc_FS,
  CUSTOM_HID_Init_FS,
  CUSTOM_HID_DeInit_FS,
  CUSTOM_HID_OutEvent_FS
};

/** @defgroup USBD_CUSTOM_HID_Private_Functions USBD_CUSTOM_HID_Private_Functions
  * @brief Private functions.
  * @{
  */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Initializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_Init_FS(void)
{
  /* USER CODE BEGIN 4 */
  return (USBD_OK);
  /* USER CODE END 4 */
}

/**
  * @brief  DeInitializes the CUSTOM HID media low layer
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_DeInit_FS(void)
{
  /* USER CODE BEGIN 5 */
  return (USBD_OK);
  /* USER CODE END 5 */
}

/**
  * @brief  Manage the CUSTOM HID class events
  * @param  event_idx: Event index
  * @param  state: Event state
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
static int8_t CUSTOM_HID_OutEvent_FS(uint8_t event_idx, uint8_t state)
{
  /* USER CODE BEGIN 6 */
  UNUSED(event_idx);
  UNUSED(state);

  /* Start next USB packet transfer once data processing is completed */
  if (USBD_CUSTOM_HID_ReceivePacket(&hUsbDeviceFS) != (uint8_t)USBD_OK)
  {
    return -1;
  }

  return (USBD_OK);
  /* USER CODE END 6 */
}

/* USER CODE BEGIN 7 */
/**
  * @brief  Send the report to the Host
  * @param  report: The report to be sent
  * @param  len: The report length
  * @retval USBD_OK if all operations are OK else USBD_FAIL
  */
/*
static int8_t USBD_CUSTOM_HID_SendReport_FS(uint8_t *report, uint16_t len)
{
  return USBD_CUSTOM_HID_SendReport(&hUsbDeviceFS, report, len);
}
*/



/* USER CODE END 7 */

/* USER CODE BEGIN PRIVATE_FUNCTIONS_IMPLEMENTATION */

/* USER CODE END PRIVATE_FUNCTIONS_IMPLEMENTATION */
/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */


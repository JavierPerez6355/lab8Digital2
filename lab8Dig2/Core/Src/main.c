/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
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
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "ili9341.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{

  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_SPI1_Init();
  /* USER CODE BEGIN 2 */
	LCD_Init(); //inicializar la pantalla

	LCD_Clear(0x0000);  // Fondo negro

	FillRect(0, 0, 320, 28, 0x52ab);

	// x=0, y=0
	// ancho=320, alto=28
	// color=0x52ab: gris

	LCD_Print("OXI-PULSE", 8, 8, 1, 0x07FF, 0x52ab);

	// x=8, y=8
	// tamaño=1
	// color=0x07FF: cian
	// fondo=0x52ab: gris

	FillRect(238, 10, 8, 8, 0x07E0);
	LCD_Print("NORMAL", 250, 8, 1, 0x07E0, 0x52ab);

	LCD_Print("%SpO2", 25, 45, 1, 0xFFFF, 0x0000);
	LCD_Print("98%", 20, 70, 3, 0x07FF, 0x0000);

	LCD_Print("PR", 190, 45, 1, 0xFFFF, 0x0000);
	LCD_Print("72", 185, 70, 3, 0x07E0, 0x0000);
	LCD_Print("BPM", 250, 84, 2, 0xFFFF, 0x0000);

	// Gota
	#define IMAGE_WGOTA  24
	#define IMAGE_HGOTA 20

	// 24 x 20 RGB565, 480 pixels, 960 bytes
	const uint16_t image_gota[] = {
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x18A2, 0x1082, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x18C3, 0x10A2, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x1946, 0x1905, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x10A2, 0x2BB5, 0x2B32, 0x1082, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x10A2, 0x2BB5, 0x2B32, 0x1082, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x10C3, 0x226D, 0x2BF7, 0x2BD6, 0x224D, 0x10A2, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0020, 0x2125, 0x2312, 0x2CFA, 0x2CDA, 0x22F1, 0x18E3, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0020,
	  0x1946, 0x2BF7, 0x2D1A, 0x35BC, 0x35BC, 0x2CFA, 0x2B74, 0x1925,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0041,
	  0x2187, 0x2C38, 0x353B, 0x5E1B, 0x55FC, 0x353B, 0x2BD5, 0x2166,
	  0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1082, 0x2188,
	  0x2C17, 0x2C79, 0x355B, 0x5E1C, 0x661B, 0x55FC, 0x357C, 0x2C38,
	  0x1925, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0841, 0x19A9, 0x22D0,
	  0x2C58, 0x35BC, 0x45DC, 0x7E7C, 0x7E7C, 0x6E5C, 0x45DC, 0x34FA,
	  0x22AF, 0x1967, 0x0020, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1082, 0x22D0, 0x3C78,
	  0x7DBB, 0x35BC, 0x561C, 0x96BD, 0x9EBD, 0x869C, 0x5E1C, 0x35BC,
	  0x2C38, 0x226D, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1082, 0x22D0, 0x54D9,
	  0xE79F, 0x3DBC, 0x561C, 0x6E3C, 0x6E3C, 0x6E3C, 0x5E1C, 0x35BC,
	  0x2C17, 0x226D, 0x0861, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x10E4, 0x2A0A,
	  0x5D1A, 0xD77E, 0x6E5D, 0x3DDC, 0x3DDC, 0x3DBC, 0x359C, 0x2C79,
	  0x21A8, 0x10A3, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1081, 0x1967,
	  0x2BB5, 0x4436, 0xA63B, 0xD73E, 0xA6BD, 0x2CFA, 0x2BD6, 0x23B5,
	  0x1905, 0x0841, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x10A2, 0x18E3, 0x226E, 0x2333, 0x2353, 0x224D, 0x10C3, 0x10A2,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0861, 0x10A2, 0x10A2, 0x0861, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
	  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
	};

	LCD_Bitmap(70, 42, IMAGE_WGOTA, IMAGE_HGOTA, image_gota);

	// Corazón
	#define IMAGE_WHEART  24
	#define IMAGE_HHEART 20

	// 24 x 20 RGB565, 480 pixels, 960 bytes
	const uint16_t image_heart[] = {
			0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x5002, 0x6803, 0x6803,
			  0x6803, 0x6003, 0x0000, 0x0000, 0x0000, 0x0000, 0x2001, 0x6803,
			  0x6803, 0x5803, 0x3803, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0800, 0x2801, 0x88E7, 0xA908, 0xA8A7,
			  0xA887, 0xA086, 0x2001, 0x0800, 0x0000, 0x2000, 0x5002, 0xA004,
			  0x9804, 0x8004, 0x5804, 0x2001, 0x1000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x2001, 0x8804, 0xE310, 0xFB92, 0xFA2D,
			  0xFA0D, 0xF1EC, 0x8804, 0x2001, 0x1000, 0x7803, 0xA804, 0xE004,
			  0xC803, 0xA004, 0x8004, 0x5804, 0x3803, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x3801, 0x6885, 0xCA4D, 0xEACF, 0xFAAF, 0xFA2D,
			  0xF16A, 0xE8C7, 0xB804, 0x7002, 0x5802, 0xB004, 0xC804, 0xE004,
			  0xC803, 0xA804, 0x8804, 0x7804, 0x6003, 0x3002, 0x0800, 0x0000,
			  0x0000, 0x0000, 0x6003, 0xA908, 0xFBF3, 0xFA8F, 0xFA0D, 0xFA0D,
			  0xE8E8, 0xE004, 0xE004, 0xA004, 0x9804, 0xD804, 0xE004, 0xE004,
			  0xC803, 0xA804, 0x8804, 0x8804, 0x7804, 0x5004, 0x1000, 0x0000,
			  0x0000, 0x0000, 0x6003, 0xA086, 0xFA2D, 0xFA0D, 0xF18B, 0xE025,
			  0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004,
			  0xC803, 0xA804, 0x8804, 0x8804, 0x7804, 0x5004, 0x1000, 0x0000,
			  0x0000, 0x0000, 0x6003, 0xA886, 0xFA0D, 0xF129, 0xE8A7, 0xE004,
			  0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004,
			  0xC803, 0xA804, 0x8804, 0x8804, 0x7804, 0x5004, 0x1000, 0x0000,
			  0x0000, 0x0000, 0x5802, 0x9866, 0xE9CC, 0xE066, 0xE004, 0xE004,
			  0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004,
			  0xC003, 0xA004, 0x8804, 0x8004, 0x7004, 0x4803, 0x1000, 0x0000,
			  0x0000, 0x0000, 0x1000, 0x3802, 0xA045, 0xD004, 0xE004, 0xE004,
			  0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xD804, 0xC803,
			  0x9804, 0x9004, 0x8004, 0x6004, 0x4803, 0x1000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x1800, 0x6803, 0xB004, 0xD004, 0xE004,
			  0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xD804, 0xC804, 0xB003,
			  0x8804, 0x8004, 0x7804, 0x4803, 0x2802, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x6803, 0x9804, 0xE004,
			  0xE004, 0xE004, 0xE004, 0xE004, 0xE004, 0xC803, 0xB004, 0x8804,
			  0x8804, 0x7004, 0x5003, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0800, 0x2801, 0x8803,
			  0xC004, 0xE004, 0xE004, 0xD003, 0xC003, 0x9804, 0x9004, 0x8804,
			  0x5804, 0x3002, 0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x1000, 0x5802,
			  0x9803, 0xC804, 0xD804, 0xB803, 0xA803, 0x9004, 0x8004, 0x7804,
			  0x4003, 0x1801, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x4802, 0x9004, 0xC003, 0x9804, 0x8804, 0x8804, 0x7004, 0x5004,
			  0x0800, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x1800, 0x4001, 0xA003, 0x9004, 0x8004, 0x6804, 0x5003, 0x2001,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x8003, 0x8004, 0x8004, 0x5004, 0x3002, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x3802, 0x4803, 0x0800, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x1801, 0x1801, 0x0000, 0x0000, 0x0000,
			  0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000, 0x0000
	};

	LCD_Bitmap(210, 42, IMAGE_WHEART, IMAGE_HHEART, image_heart);

	FillRect(10, 115, 300, 110, 0x0841);
	LCD_Print("ONDA PPG", 18, 122, 1, 0xFFFF, 0x0841);

	FillRect(18, 150, 214, 1, 0x52AB);
	FillRect(18, 180, 214, 1, 0x52AB);
	FillRect(18, 210, 214, 1, 0x52AB);


	LCD_Print("INT.", 260, 122, 1, 0xFFFF, 0x0841);  // Título del indicador

	FillRect(238, 145, 1, 68, 0x52AB);  // Separador vertical




  /* USER CODE END 2 */

	int nivelPulso = 0;  // Nivel simulado: de 0 a 7 barras

	// Altura de cada punto del pulso respecto a la línea base y=180
	const int formaPulso[25] = {
	    0, 0, 2, 8, 18, 26, 29, 28, 26, 23,
	    20, 17, 14, 11, 8, 6, 7, 10, 8, 6,
	    4, 2, 1, 0, 0
	};

	int desplazamiento = 0;  // Posición horizontal del barrido

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {



		// Borra las posiciones anteriores de la onda
		for (int copia = 0; copia < 3; copia++) {
		    for (int i = 0; i < 25; i++) {
		        int x = 23 + copia * 100 - desplazamiento + i * 4;
		        int y = 180 - formaPulso[i];

		        if (x >= 18 && x <= 228) {
		            FillRect(x, y, 4, 3, 0x0841);
		        }
		    }
		}

		// Restaura la guía central que pudo borrarse junto con la onda
		FillRect(18, 180, 214, 1, 0x52AB);

		// Avanza la onda 4 píxeles hacia la izquierda
		desplazamiento = (desplazamiento + 4) % 100;

		// Fase de intensidad: el máximo coincide con la punta entrando por la derecha
		int faseIntensidad = (desplazamiento + 80) % 100;

		if (faseIntensidad <= 48) {
		    nivelPulso = (7 * (48 - faseIntensidad) + 24) / 48;
		} else {
		    nivelPulso = (7 * (faseIntensidad - 48) + 26) / 52;
		}

		// Dibuja la onda en su nueva posición
		for (int copia = 0; copia < 4; copia++) {
		    for (int i = 0; i < 25; i++) {
		        int x = 23 + copia * 100 - desplazamiento + i * 4;
		        int y = 180 - formaPulso[i];

		        if (x >= 18 && x <= 228) {
		            FillRect(x, y, 4, 3, 0x07FF);
		        }
		    }
		}



		// Barras de abajo hacia arriba: verde, lima, amarillo, naranja y rojo
		FillRect(255, 199, 40, 5, (nivelPulso >= 1) ? 0x07E0 : 0x52AB);
		FillRect(255, 191, 40, 5, (nivelPulso >= 2) ? 0x87E0 : 0x52AB);
		FillRect(255, 183, 40, 5, (nivelPulso >= 3) ? 0xFFE0 : 0x52AB);
		FillRect(255, 175, 40, 5, (nivelPulso >= 4) ? 0xFD20 : 0x52AB);
		FillRect(255, 167, 40, 5, (nivelPulso >= 5) ? 0xF800 : 0x52AB);
		FillRect(255, 159, 40, 5, (nivelPulso >= 6) ? 0xF800 : 0x52AB);
		FillRect(255, 151, 40, 5, (nivelPulso >= 7) ? 0xF800 : 0x52AB);

		HAL_Delay(72);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	}
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 2;
  RCC_OscInitStruct.PLL.PLLR = 2;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief SPI1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_SPI1_Init(void)
{

  /* USER CODE BEGIN SPI1_Init 0 */

  /* USER CODE END SPI1_Init 0 */

  /* USER CODE BEGIN SPI1_Init 1 */

  /* USER CODE END SPI1_Init 1 */
  /* SPI1 parameter configuration*/
  hspi1.Instance = SPI1;
  hspi1.Init.Mode = SPI_MODE_MASTER;
  hspi1.Init.Direction = SPI_DIRECTION_2LINES;
  hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
  hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
  hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
  hspi1.Init.NSS = SPI_NSS_SOFT;
  hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
  hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
  hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
  hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  hspi1.Init.CRCPolynomial = 10;
  if (HAL_SPI_Init(&hspi1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN SPI1_Init 2 */

  /* USER CODE END SPI1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
  /* USER CODE BEGIN MX_GPIO_Init_1 */
  /* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_RESET_GPIO_Port, LCD_RESET_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LCD_DC_GPIO_Port, LCD_DC_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, LCD_CS_Pin|SD_CS_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_RESET_Pin */
  GPIO_InitStruct.Pin = LCD_RESET_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(LCD_RESET_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LCD_DC_Pin */
  GPIO_InitStruct.Pin = LCD_DC_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(LCD_DC_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : LCD_CS_Pin SD_CS_Pin */
  GPIO_InitStruct.Pin = LCD_CS_Pin|SD_CS_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  /* USER CODE BEGIN MX_GPIO_Init_2 */
  /* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
  /* USER CODE END Error_Handler_Debug */
}
#ifdef USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

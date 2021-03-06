/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  ** This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether 
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * COPYRIGHT(c) 2019 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

#define CLIFF_SLAVE_ADDRESS				(0xA6)
#define BATINFO_SLAVE_ADDRESS			(0xEE)
#define BATINFO_SLAVE_EXT_ADDRESS		(0x6C)

#define CLIFF_I2C_REG_CH0				(0x20)
#define CLIFF_I2C_REG_CH1				(0x22)
#define CLIFF_I2C_REG_CH2				(0x24)
#define CLIFF_I2C_REG_CH3				(0x26)
#define CLIFF_I2C_REG_CH4				(0x28)
#define CLIFF_I2C_REG_CH5				(0x2a)
#define CLIFF_I2C_REG_CH6				(0x2c)
#define CLIFF_I2C_REG_CH7				(0x2e)
#define CLIFF_I2C_REG_CHD				(0x36)

#define SEL_MODE_MAX					(2)

#define BATINFO_I2C_REG_CLIFF_LEFT		(0x0A)
#define BATINFO_I2C_REG_CLIFF_BACK		(0x0C)
#define BATINFO_I2C_REG_CLIFF_RIGHT		(0x0E)


/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef hi2c1;

TIM_HandleTypeDef htim1;

UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
uint8_t address = 0x20;		// REG_RANGE address

uint8_t data[3];
uint16_t result;

uint8_t gSelectMode;
uint8_t gSelectMode_pend;

uint16_t f2f_runtime_pre;
uint16_t f2f_runtime_now;
uint16_t f2f_runtime_result;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_TIM1_Init(void);
static void MX_I2C1_Init(void);
static void MX_USART1_UART_Init(void);
/* USER CODE BEGIN PFP */
int _write(int fd, char *str, int len);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
void readCliffDistance(uint8_t reg_address);
void readCliffCH(uint16_t delay_ms);
void readBATINFO(uint16_t delay_ms);
void touchINFO(uint16_t delay_ms);
void touchbyCliffINFO(uint16_t delay_ms);
void readBATINFOpCliff(uint16_t delay_ms);

uint16_t readI2CHalfWord(uint8_t slave_address, uint8_t reg_address);
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
  HAL_Delay(500);
  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART2_UART_Init();
  MX_TIM1_Init();
  MX_I2C1_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_TIM_Base_Start_IT(&htim1);

  // read

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */
	  // select user test program by blue button.
	  if(1){
		  switch(gSelectMode)
		  {
		  case 1:
	//		  readCliffCH(100);
			  readBATINFO(500);
	//		  readBATINFO(1000);
			  gSelectMode_pend = RESET;
			  break;
		  case 2:
			  readBATINFOpCliff(500);
			  gSelectMode_pend = RESET;
			  break;
//		  case 3:
//			  touchbyCliffINFO(5);
//			  gSelectMode_pend = RESET;
//			  break;
//		  case 4:
//			  touchINFO(5);
//			  gSelectMode_pend = RESET;
//			  break;
		  }
	  }
	  // cliff 3ch read using BAT-INFO IC
	  if(0){
		  readBATINFOpCliff(500);
	  }


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

  /**Configure the main internal regulator output voltage 
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);
  /**Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = 16;
  RCC_OscInitStruct.PLL.PLLN = 336;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV4;
  RCC_OscInitStruct.PLL.PLLQ = 7;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /**Initializes the CPU, AHB and APB busses clocks 
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
  * @brief I2C1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_I2C1_Init(void)
{

  /* USER CODE BEGIN I2C1_Init 0 */

  /* USER CODE END I2C1_Init 0 */

  /* USER CODE BEGIN I2C1_Init 1 */

  /* USER CODE END I2C1_Init 1 */
  hi2c1.Instance = I2C1;
  hi2c1.Init.ClockSpeed = 400000;
  hi2c1.Init.DutyCycle = I2C_DUTYCYCLE_2;
  hi2c1.Init.OwnAddress1 = 0;
  hi2c1.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
  hi2c1.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
  hi2c1.Init.OwnAddress2 = 0;
  hi2c1.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
  hi2c1.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;
  if (HAL_I2C_Init(&hi2c1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN I2C1_Init 2 */

  /* USER CODE END I2C1_Init 2 */

}

/**
  * @brief TIM1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_TIM1_Init(void)
{

  /* USER CODE BEGIN TIM1_Init 0 */

  /* USER CODE END TIM1_Init 0 */

  TIM_MasterConfigTypeDef sMasterConfig = {0};
  TIM_OC_InitTypeDef sConfigOC = {0};
  TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

  /* USER CODE BEGIN TIM1_Init 1 */
  // 84Mhz max
  // 8400
  // 1/10,000 = 100us
  /* USER CODE END TIM1_Init 1 */
  htim1.Instance = TIM1;
  htim1.Init.Prescaler = 8400;
  htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
  htim1.Init.Period = 9999;
  htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
  htim1.Init.RepetitionCounter = 0;
  if (HAL_TIM_OC_Init(&htim1) != HAL_OK)
  {
    Error_Handler();
  }
  sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
  sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
  if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig) != HAL_OK)
  {
    Error_Handler();
  }
  sConfigOC.OCMode = TIM_OCMODE_TIMING;
  sConfigOC.Pulse = 0;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
  sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
  if (HAL_TIM_OC_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
  {
    Error_Handler();
  }
  sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
  sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
  sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
  sBreakDeadTimeConfig.DeadTime = 0;
  sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
  sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
  sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
  if (HAL_TIMEx_ConfigBreakDeadTime(&htim1, &sBreakDeadTimeConfig) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN TIM1_Init 2 */

  /* USER CODE END TIM1_Init 2 */

}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

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

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

}

/* USER CODE BEGIN 4 */
int _write(int fd, char *str, int len)
{
	for(int i=0;i<len;i++)
	{ //UART 1번에 ?��?��?�� ?��?��
		HAL_UART_Transmit(&huart2, (uint8_t *)&str[i], 1, 0xFFFF);
	}
	return len;
}

void readCliffDistance(uint8_t reg_address)
{

	HAL_I2C_Master_Transmit(&hi2c1, 0xA6, &reg_address, 1, 1000);
	HAL_Delay(5);
	HAL_I2C_Master_Receive(&hi2c1, 0xA6, data, 2, 1000);
	HAL_Delay(5);

}
/*
 *  @reg_address
 * 	@return 		16bit data
 */


uint16_t readI2CHalfWord(uint8_t slave_address, uint8_t reg_address)
{
	uint8_t i2cdata[2];
	HAL_I2C_Master_Transmit(&hi2c1, slave_address, &reg_address, 1, 1000);
	HAL_Delay(5);
	HAL_I2C_Master_Receive(&hi2c1, slave_address, i2cdata, 2, 1000);
	HAL_Delay(5);
	return (uint16_t)((i2cdata[1]<<8) | i2cdata[0]);
}

uint16_t readI2CHalfWord_MSBf(uint8_t slave_address, uint8_t reg_address)
{
	uint8_t i2cdata[2];
	HAL_I2C_Master_Transmit(&hi2c1, slave_address, &reg_address, 1, 1000);
	HAL_Delay(5);
	HAL_I2C_Master_Receive(&hi2c1, slave_address, i2cdata, 2, 1000);
	HAL_Delay(5);
	return (uint16_t)(i2cdata[0]<<8 | i2cdata[1]);
}

void readCliffCH(uint16_t delay_ms)
{

	readCliffDistance(CLIFF_I2C_REG_CH0);
	printf("CH0:%d ",result);
	result = (uint16_t)(data[1]<<8) | data[0];		// LSB first
//	HAL_Delay(delay_ms);

//	readCliffDistance(CLIFF_I2C_REG_CH1);
//	result = (uint16_t)(data[1]<<8) | data[0];
//	printf("CH1:%d ",result);
//	HAL_Delay(delay_ms);

//	readCliffDistance(CLIFF_I2C_REG_CH2);
//	result = (uint16_t)(data[1]<<8) | data[0];
//	printf("CH2:%d ",result);
//	HAL_Delay(delay_ms);
//
//	readCliffDistance(CLIFF_I2C_REG_CH3);
//	result = (uint16_t)(data[1]<<8) | data[0];
//	printf("CH3:%d ",result);
//	HAL_Delay(delay_ms);

	readCliffDistance(CLIFF_I2C_REG_CH4);
	result = (uint16_t)(data[1]<<8) | data[0];
	printf("CH4:%d ",result);
//	HAL_Delay(delay_ms);

//	readCliffDistance(CLIFF_I2C_REG_CH5);
//	result = (uint16_t)(data[1]<<8) | data[0];
//	printf("CH5:%d ",result);
//	HAL_Delay(delay_ms);

	readCliffDistance(CLIFF_I2C_REG_CH6);
	result = (uint16_t)(data[1]<<8) | data[0];
	printf("CH6:%d ",result);
//	HAL_Delay(delay_ms);

//	readCliffDistance(CLIFF_I2C_REG_CH7);
//	result = (uint16_t)(data[1]<<8) | data[0];
//	printf("CH7:%d ",result);
//	HAL_Delay(delay_ms);
	HAL_Delay(delay_ms);
	printf("\n");
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin==GPIO_PIN_13 && gSelectMode_pend==RESET){
//		printf("blue stick appear\n");
		if(gSelectMode == SEL_MODE_MAX)
			gSelectMode = 0;
		// if click a blue user button, change the run application.
		gSelectMode++;
		printf("\n");
		printf("gSelectMode:%d\n",gSelectMode);
		gSelectMode_pend = SET;
	}

}

void readBATINFO(uint16_t delay_ms)
{
	uint16_t tmpdata;

	printf("\n#1_BATINFO MCU\n");
	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x00);
	printf("read_VCELL\t[0x00]\t:%d\n",tmpdata);
	HAL_Delay(5);

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x02);
	printf("SOC\t[0x02]\t:%d\n",tmpdata>>8 & 0xFF);
	HAL_Delay(5);

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x04);
	printf("Current\t[0x04]\t:%d,",tmpdata & 0x7FFF);
	// 15bit: charge/discharge 0:chg, 1:dis_chg
	if(tmpdata >> 15 & 0x01)
		printf("discharge\n");
	else
		printf("charge\n");

	HAL_Delay(5);

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x06);
	printf("FullCap\t[0x06]\t:%d\n",tmpdata);
	HAL_Delay(5);

	printf("\n#2_CliffHub MCU\n");

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x0A);
	printf(" Cliff left\t[0x0A]\t:%d\n",tmpdata);
	HAL_Delay(5);

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x0C);
	printf(" Cliff back\t[0x0C]\t:%d\n",tmpdata);
	HAL_Delay(5);

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x0E);
	printf(" Cliff right\t[0x0E]\t:%d\n",tmpdata);
	HAL_Delay(5);

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x10);
	printf("Touch+state\t[0x10]\t:0x%x\n",tmpdata);
	HAL_Delay(5);

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x10);
	printf("Touch[0x10](8bit)\t:%d,  %d,  %d\n",tmpdata>>8 & 0x01,tmpdata>>9 & 0x01,tmpdata>>10 & 0x01 );
	HAL_Delay(5);

	HAL_Delay(delay_ms);

	// test - confirm to function read i2c channel.
//	tmpdata = readI2CHalfWord(CLIFF_SLAVE_ADDRESS,CLIFF_I2C_REG_CH0);
//	printf("(T_func)CLIFF CH0:%d\n",tmpdata);
//	HAL_Delay(delay_ms);

}

void readBATINFOpCliff(uint16_t delay_ms)
{
	uint16_t tmpdata;

//	printf("\n#2_CliffHub MCU\n");

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,BATINFO_I2C_REG_CLIFF_RIGHT);
	printf("BatInfo Cliff {R,B,L}:\t%d\t",tmpdata);
	HAL_Delay(5);

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,BATINFO_I2C_REG_CLIFF_BACK);
	printf("%d\t",tmpdata);
	HAL_Delay(5);

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,BATINFO_I2C_REG_CLIFF_LEFT);
	printf("%d\n",tmpdata);
	HAL_Delay(5);

	HAL_Delay(delay_ms);
}

void touchINFO(uint16_t delay_ms)
{
	static uint16_t predata;
	uint16_t tmpdata;

	tmpdata = readI2CHalfWord_MSBf(BATINFO_SLAVE_EXT_ADDRESS,0x10);
//	printf("Touch[0x10](8bit)\t:%d,  %d,  %d\n",tmpdata>>8 & 0x01,tmpdata>>9 & 0x01,tmpdata>>10 & 0x01 );
	printf("Tch:BATINFO:0x%x\n",tmpdata);
//	HAL_Delay(delay_ms);

	// when value changed, time stamp
	if(tmpdata!=0 && tmpdata != predata){

		f2f_runtime_now = htim1.Instance->CNT;
		if(f2f_runtime_now < f2f_runtime_pre){
			f2f_runtime_result = (htim1.Instance->ARR + f2f_runtime_now) - f2f_runtime_pre;
		}
		else
			f2f_runtime_result = f2f_runtime_now - f2f_runtime_pre;

		// 1 = 100us
		printf("t:%dms ",f2f_runtime_result/10);

		printf("\n");

	}

	// function time scope
	f2f_runtime_pre = htim1.Instance->CNT;

	//old data save
	predata = tmpdata;

}

void touchbyCliffINFO(uint16_t delay_ms)
{
	static uint16_t predata_c;
	uint16_t tmpdata;

	tmpdata = readI2CHalfWord_MSBf(CLIFF_SLAVE_ADDRESS,0x40);
//	printf("Touch[0x10](8bit)\t:%d,  %d,  %d\n",tmpdata>>8 & 0x01,tmpdata>>9 & 0x01,tmpdata>>10 & 0x01 );
	printf("Tch:Cliff:0x%x\n",tmpdata);

	// when value changed, time stamp
	if(tmpdata!=0 && tmpdata != predata_c){

		f2f_runtime_now = htim1.Instance->CNT;
		if(f2f_runtime_now < f2f_runtime_pre){
			f2f_runtime_result = (htim1.Instance->ARR + f2f_runtime_now) - f2f_runtime_pre;
		}
		else
			f2f_runtime_result = f2f_runtime_now - f2f_runtime_pre;

		// 1 = 100us
		printf("t:%dms ",f2f_runtime_result/10);

		printf("\n");

	}

	// function time scope
	f2f_runtime_pre = htim1.Instance->CNT;

	//old data save
	predata_c = tmpdata;





//	HAL_Delay(delay_ms);

}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
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
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/

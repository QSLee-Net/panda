// ///////////////////////////////////////////////////////////// //
// Hardware abstraction layer for all different supported boards //
// ///////////////////////////////////////////////////////////// //
#include "boards/board_declarations.h"
#include "boards/unused_funcs.h"

// ///// Board definition and detection ///// //
#include "stm32f4/lladc.h"
#include "drivers/harness.h"
#include "drivers/fan.h"
#include "stm32f4/llfan.h"
#include "drivers/clock_source.h"
#include "boards/dos.h"

// Unused functions on F4
void sound_tick(void) {}

void detect_board_type(void) {
  // SPI lines floating: white (TODO: is this reliable? Not really, we have to enable ESP/GPS to be able to detect this on the UART)
  set_gpio_output(GPIOC, 14, 1);
  set_gpio_output(GPIOC, 5, 1);
  if(!detect_with_pull(GPIOB, 1, PULL_UP) && !detect_with_pull(GPIOB, 7, PULL_UP)){
    hw_type = HW_TYPE_DOS;
    current_board = &board_dos;
  } else if((detect_with_pull(GPIOA, 4, PULL_DOWN)) || (detect_with_pull(GPIOA, 5, PULL_DOWN)) || (detect_with_pull(GPIOA, 6, PULL_DOWN)) || (detect_with_pull(GPIOA, 7, PULL_DOWN))){
    // white is deprecated
  } else if(detect_with_pull(GPIOA, 13, PULL_DOWN)) { // Rev AB deprecated, so no pullup means black. In REV C, A13 is pulled up to 5V with a 10K
    // grey is deprecated
  } else if(!detect_with_pull(GPIOB, 15, PULL_UP)) {
    // uno is deprecated
  } else {
    // black is deprecated
  }

  // Return A13 to the alt mode to fix SWD
  set_gpio_alternate(GPIOA, 13, GPIO_AF0_SWJ);
}

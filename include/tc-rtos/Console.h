/*
 * consoleInterface.h
 *
 *  Created on: 07/03/2016
 *      Author: Dev
 */

#ifndef LIBS_SYSTEM_INCLUDE_CONSOLEINTERFACE_H_
#define LIBS_SYSTEM_INCLUDE_CONSOLEINTERFACE_H_




#ifdef __cplusplus
extern "C" {
#endif
	void console_write(char *output);
	void console_debug(char *format, ...);
	void  console_close();
	void console_init();
#ifdef __cplusplus
}

#endif

#endif /* LIBS_SYSTEM_INCLUDE_CONSOLEINTERFACE_H_ */


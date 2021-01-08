#ifndef _I2C_H_
#define _I2C_H_

/*
 * Low level driver for i2c bus master access
 */

#include <stdint.h>
#include <stdbool.h>
#include "i2cr.h"


#ifndef TWI_FREQ
#define TWI_FREQ 100000UL
#endif

/**
 * @brief I2C driver setup.
 */
void i2c_setup(void);

void i2c_open(void);
void i2c_close(void);


/**
 * @brief Request the driver to (asyncronously) send to `node`
 * the message of `length` bytes contained in `buffer`.
 * `status` has the state of the request:
 *  - Running: while request not scheduled
 *  - Success: when request ended satifactorily
 *  - Other values: when request ended with an error condition.
 * `status` will not be used again after request ended.
 * If the i2d driver cannot receive more requests, the call
 * blocks until this request can be accepted.
 * 
 * @param node The I2C byte address from the reciever.
 * @param buffer A pointer to a byte array where the message is saved.
 * @param length The number of bytes to be sent from the buffer.
 * @param status A pointer to an `i2cr_status_t` variable that contains the status of the request.
 */
void i2c_send(i2cr_addr_t node,
	      uint8_t *const  buffer,
	      uint8_t lenght,
	      volatile i2cr_status_t *const  status);

/**
 * @brief Request the driver to (asyncronously) receive from `node`
 * a message of `length` bytes and to store it in `buffer`.
 * `status` has the state of the request:
 *  - Running: while request not scheduled
 *  - Success: when request ended satifactorily
 *  - Other values: when request ended with an error condition.
 * `status` will not be used again after request ended.
 * If the i2d driver cannot receive more requests, the call
 * blocks until this request can be accepted.
 * 
 * @param node The I2C byte address from the sender.
 * @param buffer A pointer to a byte array where the message will be saved.
 * @param length The number of bytes to be recieved from the buffer.
 * @param status A pointer to an `i2cr_status_t` variable that contains the status of the request.
 */
void i2c_receive(i2cr_addr_t node,
		 uint8_t *const buffer,
		 uint8_t lenght,
		 volatile i2cr_status_t *const  status);


void i2c_sandr(i2cr_addr_t node,
	       uint8_t *const  s_buffer,
	       uint8_t s_lenght,
	       uint8_t *const  r_buffer,
	       uint8_t r_lenght,
	       volatile i2cr_status_t *const status);

/**
 * @brief Checks if i2c driver can receive more requests.
 * Returns true if i2 driver cannot receive more requests.
 */
bool i2c_swamped(void);


/*
 * Utility fuctions.
 * They have the same semantics that previous ones but
 * they are optimized for small messages.
 */
void i2c_send_b(i2cr_addr_t node,
		uint8_t b,
		volatile i2cr_status_t *const status);


void i2c_send_bb(i2cr_addr_t node,
		 uint16_t b,
		 volatile i2cr_status_t *const status);

void i2c_receive_b(i2cr_addr_t node,
		   uint8_t b,
		   volatile i2cr_status_t *const status);

void i2c_receive_bb(i2cr_addr_t node,
		    uint16_t b,
		    volatile i2cr_status_t *const status);


#endif

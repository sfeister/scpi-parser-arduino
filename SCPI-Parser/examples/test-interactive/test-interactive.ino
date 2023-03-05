/*-
 * BSD 2-Clause License
 *
 * Copyright (c) 2012-2018, Jan Breuer
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice,
 *   this list of conditions and the following disclaimer in the documentation
 *   and/or other materials provided with the distribution.
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

 SCPI interactive parser example

 This code is an adaptation of the "test-interactive" example from [scpi-parser].

 GitHub page for [scpi-parser]: https://github.com/j123b567/scpi-parser
 Git checkout was on March 4, 2023. Revision 4e87990.

 The following files were modified for Arduino:
   [scpi-parser]/examples/common-cxx/scpi-def.cpp
   [scpi-parser]/examples/common-cxx/scpi-def.h
   [scpi-parser]/examples/test-interactive-cxx/main.cpp

 The original [scpi-parser] code is an open project by Jan Breuer.
    Modified for Arduino by Scott Feister on March 4, 2023
    BSD license is above for the [scpi-parser] project.

*/

#include <Arduino.h>
#include "scpi-def.h"

char incoming_byte = 0; // for incoming serial data

size_t SCPI_Write(scpi_t * context, const char * data, size_t len) {
    (void) context;
    Serial.write(data, len);
    return len;
}

scpi_result_t SCPI_Flush(scpi_t * context) {
    (void) context;
    Serial.flush();
    return SCPI_RES_OK;
}

int SCPI_Error(scpi_t * context, int_fast16_t err) {
    (void) context;
    Serial.print("**ERROR: ");
    Serial.print(err);
    Serial.print(", \"");
    Serial.print(SCPI_ErrorTranslate(err));
    Serial.println("\"");
    return 0;
}

scpi_result_t SCPI_Control(scpi_t * context, scpi_ctrl_name_t ctrl, scpi_reg_val_t val) {
    (void) context;

    if (SCPI_CTRL_SRQ == ctrl) {
        Serial.print("**SRQ: 0x");
        Serial.print(val, HEX);
        Serial.print("(");
        Serial.print(val, DEC);
        Serial.println(")");
    } else {
        Serial.print("**CTRL: ");
        Serial.print(val, HEX);
        Serial.print("(");
        Serial.print(val, DEC);
        Serial.println(")");
    }
    return SCPI_RES_OK;
}

scpi_result_t SCPI_Reset(scpi_t * context) {
    (void) context;
    Serial.println("**Reset");
    return SCPI_RES_OK;
}

scpi_result_t SCPI_SystemCommTcpipControlQ(scpi_t * context) {
    (void) context;
    return SCPI_RES_ERR;
}

void setup() {
  SCPI_Init(&scpi_context,
          scpi_commands,
          &scpi_interface,
          scpi_units_def,
          SCPI_IDN1, SCPI_IDN2, SCPI_IDN3, SCPI_IDN4,
          scpi_input_buffer, SCPI_INPUT_BUFFER_LENGTH,
          scpi_error_queue_data, SCPI_ERROR_QUEUE_SIZE);

  Serial.begin(9600);
  while (!Serial); // wait for serial to finish initializing
  Serial.println("SCPI Interactive demo");
}

void loop() {
  // send data to SCPI parser only when you receive data:
  if (Serial.available() > 0) {
      incoming_byte = Serial.read();
      SCPI_Input(&scpi_context, &incoming_byte, 1);
  }
}

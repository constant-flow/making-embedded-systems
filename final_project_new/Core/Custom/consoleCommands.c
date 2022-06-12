// provided code by course "making embedded systems"
// slightly modified for this project by Constantin Wolf

// ConsoleCommands.c
// This is where you add commands:
//		1. Add a protoype
//			static eCommandResult_T ConsoleCommandVer(const char buffer[]);
//		2. Add the command to mConsoleCommandTable
//		    {"ver", &ConsoleCommandVer, HELP("Get the version string")},
//		3. Implement the function, using ConsoleReceiveParam<Type> to get the parameters from the buffer.

#include <string.h>
#include "consoleCommands.h"
#include "console.h"
#include "consoleIo.h"
#include "version.h"
#include "al_state.h"

#define IGNORE_UNUSED_VARIABLE(x) \
	if (&x == &x)                 \
	{                             \
	}

static eCommandResult_T ConsoleCommandComment(const char buffer[]);
static eCommandResult_T ConsoleCommandVer(const char buffer[]);
static eCommandResult_T ConsoleCommandHelp(const char buffer[]);
static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[]);
static eCommandResult_T ConsoleCommandSetDetectorThreshold(const char buffer[]);
static eCommandResult_T ConsoleCommandMode(const char buffer[]);

static const sConsoleCommandTable_T mConsoleCommandTable[] =
	{
		{"help     ", &ConsoleCommandHelp, HELP("Lists the commands available")},
		{"ver      ", &ConsoleCommandVer, HELP("Get the version string")},
		{"threshold", &ConsoleCommandSetDetectorThreshold, HELP("Set detector sensitivity form 0-255")},
		{"mode     ", &ConsoleCommandMode, HELP("Switch between In-PCB-Plane-Tracking / In-Front-Of-Display-Tracking: `1` for PCB, `2` for In-Front")},

		CONSOLE_COMMAND_TABLE_END // must be LAST
};

static eCommandResult_T ConsoleCommandComment(const char buffer[])
{
	// do nothing
	IGNORE_UNUSED_VARIABLE(buffer);
	return COMMAND_SUCCESS;
}

static eCommandResult_T ConsoleCommandHelp(const char buffer[])
{
	uint32_t i;
	uint32_t tableLength;
	eCommandResult_T result = COMMAND_SUCCESS;

	IGNORE_UNUSED_VARIABLE(buffer);

	tableLength = sizeof(mConsoleCommandTable) / sizeof(mConsoleCommandTable[0]);
	ConsoleIoSendString(STR_ENDLINE);
	ConsoleIoSendString("╭──────────────────────────────\r\n");
	for (i = 0u; i < tableLength - 1u; i++)
	{
		ConsoleIoSendString("│ ");

		ConsoleIoSendString(mConsoleCommandTable[i].name);
#if CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(" : ");
		ConsoleIoSendString(mConsoleCommandTable[i].help);
#endif // CONSOLE_COMMAND_MAX_HELP_LENGTH > 0
		ConsoleIoSendString(STR_ENDLINE);
	}
	ConsoleIoSendString("╰──────────────────────────────\r\n");
	return result;
}

static eCommandResult_T ConsoleCommandParamExampleInt16(const char buffer[])
{
	int16_t parameterInt;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &parameterInt);
	if (COMMAND_SUCCESS == result)
	{
		ConsoleIoSendString("Parameter is ");
		ConsoleSendParamInt16(parameterInt);
		ConsoleIoSendString(" (0x");
		ConsoleSendParamHexUint16((uint16_t)parameterInt);
		ConsoleIoSendString(")");
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}
static eCommandResult_T ConsoleCommandSetDetectorThreshold(const char buffer[])
{
	int16_t threshold;
	eCommandResult_T result;
	result = ConsoleReceiveParamInt16(buffer, 1, &threshold);
	if (COMMAND_SUCCESS == result)
	{
		if (state_set_tracking_threshold(threshold))
		{
			ConsoleIoSendString("Changed detector threshold");
		}
		else
		{
			ConsoleIoSendString("Error: detector threshold not in bounds (every sound : 0 - 255 : loud sounds)");
			result = COMMAND_ERROR;
		}

		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandMode(const char buffer[])
{
	int16_t mode;
	eCommandResult_T result = ConsoleReceiveParamInt16(buffer, 1, &mode);
	if (COMMAND_SUCCESS == result)
	{
		if (mode == 1)
		{
			ConsoleIoSendString("Set to PCB-Plane Tracking");
			state_set_tracking_mode(1);
		}
		else if (mode == 2)
		{
			ConsoleIoSendString("Set to In-Front-Of-Screen Tracking");
			state_set_tracking_mode(2);
		}
		else
		{
			ConsoleIoSendString("Unknown Mode set, either use `1`(PCB-Plane) or `2`(In-Front-Of-Screen)");
			result = COMMAND_PARAMETER_ERROR;
		}

		ConsoleIoSendString(STR_ENDLINE);

		// ConsoleSendParamHexUint16(parameterUint16);
		// ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandThreshold(const char buffer[])
{
	uint16_t parameterUint16;
	eCommandResult_T result;
	result = ConsoleReceiveParamHexUint16(buffer, 1, &parameterUint16);
	if (COMMAND_SUCCESS == result)
	{
		ConsoleIoSendString("Parameter is 0x");
		ConsoleSendParamHexUint16(parameterUint16);
		ConsoleIoSendString(STR_ENDLINE);
	}
	return result;
}

static eCommandResult_T ConsoleCommandVer(const char buffer[])
{
	eCommandResult_T result = COMMAND_SUCCESS;

	IGNORE_UNUSED_VARIABLE(buffer);

	ConsoleIoSendString(VERSION_STRING);
	ConsoleIoSendString(STR_ENDLINE);
	return result;
}

const sConsoleCommandTable_T *ConsoleCommandsGetTable(void)
{
	return (mConsoleCommandTable);
}

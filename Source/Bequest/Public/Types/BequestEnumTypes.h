#pragma once

UENUM()
enum class EBequestConfirmType : uint8
{
	Yes,
	No
};

UENUM()
enum class EBequestValidType : uint8
{
	Valid,
	Invalid
};

UENUM()
enum class EBequestResultType : uint8
{
	Success,
	Failure
};
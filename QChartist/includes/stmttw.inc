'CONST MM_MCINOTIFY=&H3B9
CONST TEXT_BUFFER_SIZE=5000
CONST NEW_TTS_ALWAYS=1
CONST REUSE_CURRENT_TTS=2
CONST MIN_VOLUME=0
CONST MAX_VOLUME=&HFFFFFFFF
CONST MIN_PITCH=0
CONST MAX_PITCH=&HFFFF
CONST MIN_SPEED=0
CONST MAX_SPEED=&HFFFFFFFF
CONST USE_DEFAULT_VOLUME=0
CONST USE_DEFINED_VOLUME=1
CONST USE_DEFAULT_PITCH=0
CONST USE_DEFINED_PITCH=1
CONST USE_DEFAULT_SPEED=0
CONST USE_DEFINED_SPEED=1
CONST USE_TEXT=0
CONST USE_CLIPBOARD=1
CONST DONT_CLEAR_BUFFERS=0
CONST CLEAR_TEXT_BUFFER=1
CONST CLEAR_SPEECH_BUFFER=2
CONST CLEAR_TEXTSPEECH_BUFFER=3
CONST OPEN_CD_DOOR=0
CONST CLOSE_CD_DOOR=1
CONST OPEN_DEFAULT_DOOR=0
CONST OPEN_MYLETTER_DOOR=1
CONST QUIET_BEEPSOUND=0
CONST QUIET_NOBEEP=1
CONST DO_NOT_WAIT=0
CONST WAIT_FOR_COMPLETION=1
CONST NO_NOTIFICATION=0
CONST MODE_NOT_READY=524
CONST MODE_STOP=525
CONST MODE_PLAY=526
CONST MODE_RECORD=527
CONST MODE_SEEK=528
CONST MODE_PAUSE=529
CONST MODE_OPEN=530
CONST MONO_CHANNELS=1
CONST STEREO_CHANNELS=2
'CONST WAVE_MAPPER=-1
CONST SOUND_CARD=0
'CONST MIDI_MAPPER=-1
CONST NO_MIDI_PAUSE=0
CONST MIDI_PAUSE=1
'CONST WHDR_DONE=1
'CONST WHDR_PREPARED=2
'CONST WHDR_BEGINLOOP=4
'CONST WHDR_ENDLOOP=8
'CONST WHDR_INQUEUE=16
'CONST MMSYSERR_NOERROR=0
'CONST MMSYSERR_ERROR=1
'CONST MMSYSERR_BADDEVICEID=2
'CONST MMSYSERR_NOTENABLED=3
'CONST MMSYSERR_ALLOCATED=4
'CONST MMSYSERR_INVALHANDLE=5
'CONST MMSYSERR_NODRIVER=6
'CONST MMSYSERR_NOMEM=7
'CONST MMSYSERR_NOTSUPPORTED=8
'CONST MMSYSERR_BADERRNUM=9
'CONST MMSYSERR_INVALFLAG=10
'CONST MMSYSERR_INVALPARAM=11
'CONST MMSYSERR_HANDLEBUSY=12
'CONST MMSYSERR_INVALIDALIAS=13
CONST MMSYSERR_BADDB=14
CONST MMSYSERR_KEYNOTFOUND=15
CONST MMSYSERR_READERROR=16
CONST MMSYSERR_WRITEERROR=17
CONST MMSYSERR_DELETEERROR=18
CONST MMSYSERR_VALNOTFOUND=19
CONST MMSYSERR_NODRIVERCB=20
'CONST MM_WIM_DATA=&H3C0
'CONST WM_CLOSE=16
'CONST FALSE=0
'CONST TRUE=1

Declare Function MEM_Allocate Lib "stm.dll" Alias "MEM_Allocate" (bufferSize As Long) As Long
Declare Function MEM_GetAddress Lib "stm.dll" Alias "MEM_GetAddress" () As Long
Declare Function MEM_Deallocate Lib "stm.dll" Alias "MEM_Deallocate" () As Long
Declare Function IMEM_Allocate Lib "stm.dll" Alias "IMEM_Allocate" (bufferSize As Long) As Long
Declare Function IMEM_GetAddress Lib "stm.dll" Alias "IMEM_GetAddress" () As Long
Declare Function IMEM_Deallocate Lib "stm.dll" Alias "IMEM_Deallocate" () As Long
Declare Function OMEM_Allocate Lib "stm.dll" Alias "OMEM_Allocate" (bufferSize As Long) As Long
Declare Function OMEM_GetAddress Lib "stm.dll" Alias "OMEM_GetAddress" () As Long
Declare Function OMEM_Deallocate Lib "stm.dll" Alias "OMEM_Deallocate" () As Long

Declare Function Get_WinVer Lib "stm.dll" Alias "Get_WinVer" () As Long
Declare Function CD_Door Lib "stm.dll" Alias "CD_Door" (openClose As Long, useDefDrive As Long, cdDriveLetter As String) As Long
Declare Function WAVFile_LoadIntoMemory Lib "stm.dll" Alias "WAVFile_LoadIntoMemory" (fname As String) As Long
Declare Function SyncWAV_Play Lib "stm.dll" Alias "SyncWAV_Play" (fname As String, quietMode As Long) As Long
Declare Function AsyncWAV_Play Lib "stm.dll" Alias "AsyncWAV_Play" (fname As String, quietMode As Long) As Long
Declare Function AsyncWAV_LoopPlay Lib "stm.dll" Alias "AsyncWAV_LoopPlay" (fname As String, quietMode As Long) As Long
Declare Function WAV_StopAll Lib "stm.dll" Alias "WAV_StopAll" () As Long

Declare Function MCI_SendCommand Lib "stm.dll" Alias "MCI_SendCommand" (id As Long, message As Long, flags As Long, structAdr As Long) As Long
Declare Function MCI_SendString Lib "stm.dll" Alias "MCI_SendString" (command As String, buffer As Long, bufSize As Long, hWindow As Long) As Long
Declare Function MCI_GetErrorString Lib "stm.dll" Alias "MCI_GetErrorString" (errorNumber As Long) As Long

Declare Function MCIDevice_Open Lib "stm.dll" Alias "MCIDevice_Open" (deviceName As String, fname As String) As Long
Declare Function MCIDevice_GetCapabilities Lib "stm.dll" Alias "MCIDevice_GetCapabilities" (hWindow As Long, flags As Long, waitMode As Long) As Long
Declare Function MCIDevice_QueryDeviceType Lib "stm.dll" Alias "MCIDevice_QueryDeviceType" (hWindow As Long, waitMode As Long) As Long
Declare Function MCIDevice_QueryAudioOutput Lib "stm.dll" Alias "MCIDevice_QueryAudioOutput" (hWindow As Long, waitMode As Long) As Long
Declare Function MCIDevice_QueryVideoOutput Lib "stm.dll" Alias "MCIDevice_QueryVideoOutput" (hWindow As Long, waitMode As Long) As Long
Declare Function MCIDevice_QueryEjectMedia Lib "stm.dll" Alias "MCIDevice_QueryEjectMedia" (hWindow As Long, waitMode As Long) As Long
Declare Function MCIDevice_QueryPlayMedia Lib "stm.dll" Alias "MCIDevice_QueryPlayMedia" (hWindow As Long, waitMode As Long) As Long
Declare Function MCIDevice_QueryRecordMedia Lib "stm.dll" Alias "MCIDevice_QueryRecordMedia" (hWindow As Long, waitMode As Long) As Long
Declare Function MCIDevice_Record Lib "stm.dll" Alias "MCIDevice_Record" (hWindow As Long, waitMode As Long) As Long
Declare Function MCIDevice_RecordFrom Lib "stm.dll" Alias "MCIDevice_RecordFrom" (hWindow As Long, start As Long, waitMode As Long) As Long
Declare Function MCIDevice_RecordTo Lib "stm.dll" Alias "MCIDevice_RecordTo" (hWindow As Long, end As Long, waitMode As Long) As Long
Declare Function MCIDevice_RecordFromTo Lib "stm.dll" Alias "MCIDevice_RecordFromTo" (hWindow As Long, start As Long, end As Long, waitMode As Long) As Long
Declare Function MCIDevice_Play Lib "stm.dll" Alias "MCIDevice_Play" (hWindow As Long, waitMode As Long) As Long
Declare Function MCIDevice_PlayFrom Lib "stm.dll" Alias "MCIDevice_PlayFrom" (hWindow As Long, start As Long, waitMode As Long) As Long
Declare Function MCIDevice_PlayTo Lib "stm.dll" Alias "MCIDevice_PlayTo" (hWindow As Long, end As Long, waitMode As Long) As Long
Declare Function MCIDevice_PlayFromTo Lib "stm.dll" Alias "MCIDevice_PlayFromTo" (hWindow As Long, start As Long, end As Long, waitMode As Long) As Long
Declare Function MCIDevice_SaveFile Lib "stm.dll" Alias "MCIDevice_SaveFile" (hWindow As Long, fname As String, waitMode As Long) As Long
Declare Function MCIDevice_Set Lib "stm.dll" Alias "MCIDevice_Set" (hWindow As Long, waitMode As Long) As Long
Declare Function MCIDevice_SetTimeFormat Lib "stm.dll" Alias "MCIDevice_SetTimeFormat" () As Long
Declare Function MCIDevice_LeftChannelOFF Lib "stm.dll" Alias "MCIDevice_LeftChannelOFF" () As Long
Declare Function MCIDevice_LeftChannelON Lib "stm.dll" Alias "MCIDevice_LeftChannelON" () As Long
Declare Function MCIDevice_RightChannelOFF Lib "stm.dll" Alias "MCIDevice_RightChannelOFF" () As Long
Declare Function MCIDevice_RightChannelON Lib "stm.dll" Alias "MCIDevice_RightChannelON" () As Long
Declare Function MCIDevice_AllChannelsOFF Lib "stm.dll" Alias "MCIDevice_AllChannelsOFF" () As Long
Declare Function MCIDevice_AllChannelsON Lib "stm.dll" Alias "MCIDevice_AllChannelsON" () As Long
Declare Function MCIDevice_Close Lib "stm.dll" Alias "MCIDevice_Close" (waitMode As Long) As Long

Declare Function WAVDeviceO_CountDevices Lib "stm.dll" Alias "WAVDeviceO_CountDevices" () As Long
Declare Function WAVDeviceO_FormatQuery Lib "stm.dll" Alias "WAVDeviceO_FormatQuery" (id As Long, numChannels As Long, samplesPerSec As Long, avrgBytesPerSec As Long, blockAlignment As Long, bitsPerSample As Long, hWindow As Long) As Long
Declare Function WAVDeviceO_Open Lib "stm.dll" Alias "WAVDeviceO_Open" (id As Long, numChannels As Long, samplesPerSec As Long, avrgBytesPerSec As Long, blockAlignment As Long, bitsPerSample As Long) As Long
Declare Function WAVDeviceO_OpenFromMemory Lib "stm.dll" Alias "WAVDeviceO_OpenFromMemory" (id As Long) As Long
Declare Function WAVDeviceO_GetCurrentPosition Lib "stm.dll" Alias "WAVDeviceO_GetCurrentPosition" () As Long
Declare Function WAVDeviceO_GetCapabilities Lib "stm.dll" Alias "WAVDeviceO_GetCapabilities" () As Long
Declare Function WAVDeviceO_GetID Lib "stm.dll" Alias "WAVDeviceO_GetID" () As Long
Declare Function WAVDeviceO_GetVolumeInfo Lib "stm.dll" Alias "WAVDeviceO_GetVolumeInfo" () As Long
Declare Function WAVDeviceO_GetPitchInfo Lib "stm.dll" Alias "WAVDeviceO_GetPitchInfo" () As Long
Declare Function WAVDeviceO_GetFormatInfo Lib "stm.dll" Alias "WAVDeviceO_GetFormatInfo" () As Long
Declare Function WAVDeviceO_GetSyncInfo Lib "stm.dll" Alias "WAVDeviceO_GetSyncInfo" () As Long
Declare Function WAVDeviceO_GetPlaybackInfo Lib "stm.dll" Alias "WAVDeviceO_GetPlaybackInfo" () As Long
Declare Function WAVDeviceO_GetSAPInfo Lib "stm.dll" Alias "WAVDeviceO_GetSAPInfo" () As Long
Declare Function WAVDeviceO_GetDeviceName Lib "stm.dll" Alias "WAVDeviceO_GetDeviceName" () As String
Declare Function WAVDeviceO_GetProductID Lib "stm.dll" Alias "WAVDeviceO_GetProductID" () As Long
Declare Function WAVDeviceO_GetManufacturerID Lib "stm.dll" Alias "WAVDeviceO_GetManufacturerID" () As Long
Declare Function WAVDeviceO_GetDriverVersion Lib "stm.dll" Alias "WAVDeviceO_GetDriverVersion" () As Long
Declare Function WAVDeviceO_GetVolume Lib "stm.dll" Alias "WAVDeviceO_GetVolume" () As Long
Declare Function WAVDeviceO_SetVolume Lib "stm.dll" Alias "WAVDeviceO_SetVolume" (newVolume As Long) As Long
Declare Function WAVDeviceO_GetPitch Lib "stm.dll" Alias "WAVDeviceO_GetPitch" () As Long
Declare Function WAVDeviceO_SetPitch Lib "stm.dll" Alias "WAVDeviceO_SetPitch" (newPitch As Long) As Long
Declare Function WAVDeviceO_PrepareBuffer Lib "stm.dll" Alias "WAVDeviceO_PrepareBuffer" () As Long
Declare Function WAVDeviceO_PlayInputBuffer Lib "stm.dll" Alias "WAVDeviceO_PlayInputBuffer" () As Long
Declare Function WAVDeviceO_Play Lib "stm.dll" Alias "WAVDeviceO_Play" () As Long
Declare Function WAVDeviceO_PlayBuffer Lib "stm.dll" Alias "WAVDeviceO_PlayBuffer" (numLoops As Long) As Long
Declare Function WAVDeviceO_UnPrepareBuffer Lib "stm.dll" Alias "WAVDeviceO_UnPrepareBuffer" () As Long
Declare Function WAVDeviceO_Pause Lib "stm.dll" Alias "WAVDeviceO_Pause" () As Long
Declare Function WAVDeviceO_UnPause Lib "stm.dll" Alias "WAVDeviceO_UnPause" () As Long
Declare Function WAVDeviceO_SetPlaybackRate Lib "stm.dll" Alias "WAVDeviceO_SetPlaybackRate" (newRate As Long) As Long
Declare Function WAVDeviceO_Stop Lib "stm.dll" Alias "WAVDeviceO_Stop" () As Long
Declare Function WAVDeviceO_Close Lib "stm.dll" Alias "WAVDeviceO_Close" () As Long

Declare Function WAVDeviceI_CountDevices Lib "stm.dll" Alias "WAVDeviceI_CountDevices" () As Long
Declare Function WAVDeviceI_FormatQuery Lib "stm.dll" Alias "WAVDeviceI_FormatQuery" (id As Long, numChannels As Long, samplesPerSec As Long, avrgBytesPerSec As Long, blockAlignment As Long, bitsPerSample As Long, hWindow As Long) As Long
Declare Function WAVDeviceI_Open Lib "stm.dll" Alias "WAVDeviceI_Open" (id As Long, numChannels As Long, samplesPerSec As Long, avrgBytesPerSec As Long, blockAlignment As Long, bitsPerSample As Long) As Long
Declare Function WAVDeviceI_GetCurrentPosition Lib "stm.dll" Alias "WAVDeviceI_GetCurrentPosition" () As Long
Declare Function WAVDeviceI_GetCapabilities Lib "stm.dll" Alias "WAVDeviceI_GetCapabilities" () As Long
Declare Function WAVDeviceI_GetID Lib "stm.dll" Alias "WAVDeviceI_GetID" () As Long
Declare Function WAVDeviceI_GetFormatInfo Lib "stm.dll" Alias "WAVDeviceI_GetFormatInfo" () As Long
Declare Function WAVDeviceI_GetDeviceName Lib "stm.dll" Alias "WAVDeviceI_GetDeviceName" () As String
Declare Function WAVDeviceI_GetProductID Lib "stm.dll" Alias "WAVDeviceI_GetProductID" () As Long
Declare Function WAVDeviceI_GetManufacturerID Lib "stm.dll" Alias "WAVDeviceI_GetManufacturerID" () As Long
Declare Function WAVDeviceI_GetDriverVersion Lib "stm.dll" Alias "WAVDeviceI_GetDriverVersion" () As Long
Declare Function WAVDeviceI_PrepareBuffer Lib "stm.dll" Alias "WAVDeviceI_PrepareBuffer" () As Long
Declare Function WAVDeviceI_AddBuffer Lib "stm.dll" Alias "WAVDeviceI_AddBuffer" () As Long
Declare Function WAVDeviceI_UnPrepareBuffer Lib "stm.dll" Alias "WAVDeviceI_UnPrepareBuffer" () As Long
Declare Function WAVDeviceI_SendMessage Lib "stm.dll" Alias "WAVDeviceI_SendMessage" (message As Long, param1 As Long, param2 As Long) As Long
Declare Function WAVDeviceI_Start Lib "stm.dll" Alias "WAVDeviceI_Start" () As Long
Declare Function WAVDeviceI_StartFinish Lib "stm.dll" Alias "WAVDeviceI_StartFinish" () As Long
Declare Function WAVDeviceI_Stop Lib "stm.dll" Alias "WAVDeviceI_Stop" () As Long
Declare Function WAVDeviceI_Reset Lib "stm.dll" Alias "WAVDeviceI_Reset" () As Long
Declare Function WAVDeviceI_Close Lib "stm.dll" Alias "WAVDeviceI_Close" () As Long

Declare Function MIDIDevice_OpenFile Lib "stm.dll" Alias "MIDIDevice_OpenFile" (fname As String) As Long
Declare Function MIDIDevice_Play Lib "stm.dll" Alias "MIDIDevice_Play" (hWindow As Long, waitMode As Long) As Long
Declare Function MIDIDevice_PlayFrom Lib "stm.dll" Alias "MIDIDevice_PlayFrom" (hWindow As Long, start As Long, waitMode As Long) As Long
Declare Function MIDIDevice_PlayTo Lib "stm.dll" Alias "MIDIDevice_PlayTo" (hWindow As Long, end As Long, waitMode As Long) As Long
Declare Function MIDIDevice_PlayFromTo Lib "stm.dll" Alias "MIDIDevice_PlayFromTo" (hWindow As Long, start As Long, end As Long, waitMode As Long) As Long
Declare Function MIDIDevice_QueryMapper Lib "stm.dll" Alias "MIDIDevice_QueryMapper" () As Long
Declare Function MIDIDevice_Pause Lib "stm.dll" Alias "MIDIDevice_Pause" (WaitMode As Long) As Long
Declare Function MIDIDevice_UnPause Lib "stm.dll" Alias "MIDIDevice_UnPause" (WaitMode As Long) As Long
Declare Function MIDIDevice_StopAll Lib "stm.dll" Alias "MIDIDevice_StopAll" (hWindow As Long, waitMode As Long) As Long
Declare Function MIDIDevice_CloseFile Lib "stm.dll" Alias "MIDIDevice_CloseFile" (waitMode As Long) As Long

Declare Function MIDIDeviceO_CountDevices Lib "stm.dll" Alias "MIDIDeviceO_CountDevices" () As Long
Declare Function MIDIDeviceO_Open Lib "stm.dll" Alias "MIDIDeviceO_Open" (id As Long, hWindow As Long) As Long
Declare Function MIDIDeviceO_GetCapabilities Lib "stm.dll" Alias "MIDIDeviceO_GetCapabilities" () As Long
Declare Function MIDIDeviceO_GetID Lib "stm.dll" Alias "MIDIDeviceO_GetID" () As Long
Declare Function MIDIDeviceO_GetVoicesInfo Lib "stm.dll" Alias "MIDIDeviceO_GetVoicesInfo" () As Long
Declare Function MIDIDeviceO_GetNotesInfo Lib "stm.dll" Alias "MIDIDeviceO_GetNotesInfo" () As Long
Declare Function MIDIDeviceO_GetChannelInfo Lib "stm.dll" Alias "MIDIDeviceO_GetChannelInfo" () As Long
Declare Function MIDIDeviceO_GetVolumeInfo Lib "stm.dll" Alias "MIDIDeviceO_GetVolumeInfo" () As Long
Declare Function MIDIDeviceO_GetCacheInfo Lib "stm.dll" Alias "MIDIDeviceO_GetCacheInfo" () As Long
Declare Function MIDIDeviceO_GetDeviceName Lib "stm.dll" Alias "MIDIDeviceO_GetDeviceName" () As String
Declare Function MIDIDeviceO_GetProductID Lib "stm.dll" Alias "MIDIDeviceO_GetProductID" () As Long
Declare Function MIDIDeviceO_GetManufacturerID Lib "stm.dll" Alias "MIDIDeviceO_GetManufacturerID" () As Long
Declare Function MIDIDeviceO_GetDriverVersion Lib "stm.dll" Alias "MIDIDeviceO_GetDriverVersion" () As Long
Declare Function MIDIDeviceO_GetVolume Lib "stm.dll" Alias "MIDIDeviceO_GetVolume" () As Long
Declare Function MIDIDeviceO_SetVolume Lib "stm.dll" Alias "MIDIDeviceO_SetVolume" (newVolume As Long) As Long
Declare Function MIDIDeviceO_PlayNote Lib "stm.dll" Alias "MIDIDeviceO_PlayNote" (message As Long, pause As Long, msecs As Long) As Long
Declare Function MIDIDeviceO_SendMessage Lib "stm.dll" Alias "MIDIDeviceO_SendMessage" (message As Long) As Long
Declare Function MIDIDeviceO_PlayStream Lib "stm.dll" Alias "MIDIDeviceO_PlayStream" () As Long
Declare Function MIDIDeviceO_StopClearAll Lib "stm.dll" Alias "MIDIDeviceO_StopClearAll" () As Long
Declare Function MIDIDeviceO_Close Lib "stm.dll" Alias "MIDIDeviceO_Close" () As Long

Declare Function CDDevice_Open Lib "stm.dll" Alias "CDDevice_Open" () As Long
Declare Function CDDevice_OpenWithTime Lib "stm.dll" Alias "CDDevice_OpenWithTime" () As Long
Declare Function CDDevice_SetTimeFormat Lib "stm.dll" Alias "CDDevice_SetTimeFormat" () As Long
Declare Function CDDevice_LeftChannelOFF Lib "stm.dll" Alias "CDDevice_LeftChannelOFF" () As Long
Declare Function CDDevice_LeftChannelON Lib "stm.dll" Alias "CDDevice_LeftChannelON" () As Long
Declare Function CDDevice_RightChannelOFF Lib "stm.dll" Alias "CDDevice_RightChannelOFF" () As Long
Declare Function CDDevice_RightChannelON Lib "stm.dll" Alias "CDDevice_RightChannelON" () As Long
Declare Function CDDevice_AllChannelsOFF Lib "stm.dll" Alias "CDDevice_AllChannelsOFF" () As Long
Declare Function CDDevice_AllChannelsON Lib "stm.dll" Alias "CDDevice_AllChannelsON" () As Long
Declare Function CDDevice_CountSongs Lib "stm.dll" Alias "CDDevice_CountSongs" () As Long
Declare Function CDDevice_GetCurrentSongNumber Lib "stm.dll" Alias "CDDevice_GetCurrentSongNumber" () As Long
Declare Function CDDevice_GetCDPosition Lib "stm.dll" Alias "CDDevice_GetCDPosition" () As Long
Declare Function CDDevice_GetCDLength Lib "stm.dll" Alias "CDDevice_GetCDLength" () As Long
Declare Function CDDevice_GetSongPosition Lib "stm.dll" Alias "CDDevice_GetSongPosition" (songNumber As Long) As Long
Declare Function CDDevice_GetSongLength Lib "stm.dll" Alias "CDDevice_GetSongLength" (songNumber As Long) As Long
Declare Function CDDevice_GetCDTime Lib "stm.dll" Alias "CDDevice_GetCDTime" () As Long
Declare Function CDDevice_GetSongTime Lib "stm.dll" Alias "CDDevice_GetSongTime" (songNumber As Long) As Long
Declare Function CDDevice_GetCurrentMode Lib "stm.dll" Alias "CDDevice_GetCurrentMode" () As Long
Declare Function CDDevice_FindFirstSong Lib "stm.dll" Alias "CDDevice_FindFirstSong" () As Long
Declare Function CDDevice_GetSongType Lib "stm.dll" Alias "CDDevice_GetSongType" () As Long
Declare Function CDDevice_IsEmpty Lib "stm.dll" Alias "CDDevice_IsEmpty" () As Long
Declare Function CDDevice_OpenDoor Lib "stm.dll" Alias "CDDevice_OpenDoor" () As Long
Declare Function CDDevice_CloseDoor Lib "stm.dll" Alias "CDDevice_CloseDoor" (waitMode As Long) As Long
Declare Function CDDevice_PlaySong Lib "stm.dll" Alias "CDDevice_PlaySong" (hWindow As Long, songNumber As Long, waitMode As Long) As Long
Declare Function CDDevice_PlaySongs Lib "stm.dll" Alias "CDDevice_PlaySongs" (hWindow As Long, startSong As Long, endSong As Long, waitMode As Long) As Long
Declare Function CDDevice_PlayCurrentSong Lib "stm.dll" Alias "CDDevice_PlayCurrentSong" (hWindow As Long, waitMode As Long) As Long
Declare Function CDDevice_PlayAllSongs Lib "stm.dll" Alias "CDDevice_PlayAllSongs" (hWindow As Long, waitMode As Long) As Long
Declare Function CDDevice_MoveToCDStart Lib "stm.dll" Alias "CDDevice_MoveToCDStart" (waitMode As Long) As Long
Declare Function CDDevice_MoveToCDEnd Lib "stm.dll" Alias "CDDevice_MoveToCDEnd" (hWindow As Long, waitMode As Long) As Long
Declare Function CDDevice_MoveToNewSong Lib "stm.dll" Alias "CDDevice_MoveToNewSong" (hWindow As Long, waitMode As Long, songNumber As Long) As Long
Declare Function CDDevice_PauseCD Lib "stm.dll" Alias "CDDevice_PauseCD" (WaitMode As Long) As Long
Declare Function CDDevice_ResumeCD Lib "stm.dll" Alias "CDDevice_ResumeCD" (WaitMode As Long) As Long
Declare Function CDDevice_StopAll Lib "stm.dll" Alias "CDDevice_StopAll" (hWindow As Long, waitMode As Long) As Long
Declare Function CDDevice_Close Lib "stm.dll" Alias "CDDevice_Close" (waitMode As Long) As Long

Declare Function Begin_Speech Lib "stm.dll" Alias "Begin_Speech" (bufSize As Long) As Long
Declare Function Count_Voices Lib "stm.dll" Alias "Count_Voices" () As Long
Declare Function Enum_VoiceData Lib "stm.dll" Alias "Enum_VoiceData" () As Long
Declare Function Enum_VoiceNames Lib "stm.dll" Alias "Enum_VoiceNames" () As Long
Declare Function Get_VoiceData Lib "stm.dll" Alias "Get_VoiceData" (index As Long) As Long
Declare Function Get_VoiceName Lib "stm.dll" Alias "Get_VoiceName" (index As Long) As Long
Declare Function Speak_String Lib "stm.dll" Alias "Speak_String" (uvt As Long, textAdr As Long, clearBuf As Long, voiceNumber As Long, delkeep As Long, useV As Long, volume As Long, useP As Long, pitch As Long, useS As Long, speed As Long) As Long
Declare Function Pause_Speech Lib "stm.dll" Alias "Pause_Speech" () As Long
Declare Function Stop_Speech Lib "stm.dll" Alias "Stop_Speech" () As Long
Declare Function Resume_Speech Lib "stm.dll" Alias "Resume_Speech" () As Long
Declare Function Tag_Speech Lib "stm.dll" Alias "Tag_Speech" (tagStg As String) As Long
Declare Function Delete_Speech Lib "stm.dll" Alias "Delete_Speech" () As Long
Declare Function Get_Volume Lib "stm.dll" Alias "Get_Volume" (voiceNumber As Long) As Long
Declare Function Get_Pitch Lib "stm.dll" Alias "Get_Pitch" (voiceNumber As Long) As Long
Declare Function Get_Speed Lib "stm.dll" Alias "Get_Speed" (voiceNumber As Long) As Long
Declare Function End_Speech Lib "stm.dll" Alias "End_Speech" () As Long
Declare Function Save_WAVFileEx Lib "ttw.dll" Alias "Save_WAVFileEx" (wavName As String, bufSize As Long, uvt As Long, textAdr As Long, clearBuf As Long, voiceNumber As Long, useV As Long, volume As Long, useP As Long, pitch As Long, useS As Long, speed As Long) As Long
Declare Function Save_WAVFile Lib "ttw.dll" Alias "Save_WAVFile" (wavName As String, voiceNumber As Long, textAdr As Long) As Long

Declare Sub CopyMemory Lib "kernel32.dll" Alias "RtlMoveMemory" (ByVal dest As Long, ByVal source As Long, ByVal numBytes As Long)

/* This file is part of BabyMINDupack
 *
 * BabyMINDupack is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * BabyMINDupack is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with BabyMINDupack.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "MDdataWordBM.h"

using namespace std;

uint32_t MDdataWordBM::GetDataType() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & DataTypeMask ) >> DataTypeShift );
  return 0;
}

uint32_t MDdataWordBM::GetBoardId() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & BoardIdMask ) >> BoardIdShift );
  return 0;
}

uint32_t MDdataWordBM::GetSpillTag() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & SpillTagMask ) >> SpillTagShift );
  return 0;
}

uint32_t MDdataWordBM::GetSpillTime() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & SpillTimeMask ) >> SpillTimeShift );
  return 0;
}

uint32_t MDdataWordBM::GetChannelId() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & ChannelIdMask ) >> ChannelIdShift );
  return 0;
}

uint32_t MDdataWordBM::GetHitTime() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & HitTimeMask ) >> HitTimeShift );
  return 0;
}

uint32_t MDdataWordBM::GetHitId() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & HitIdMask ) >> HitIdShift );
  return 0;
}

uint32_t MDdataWordBM::GetHitCount() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & HitCountMask ) >> HitCountShift );
  return 0;
}

uint32_t MDdataWordBM::GetEdgeId() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & EdgeIdMask ) >> EdgeIdShift );
  return 0;
}

uint32_t MDdataWordBM::GetTriggerTime() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & TriggerTimeMask ) >> TriggerTimeShift );
  return 0;
}

uint32_t MDdataWordBM::GetTriggerTag() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & TriggerTagMask ) >> TriggerTagShift );
  return 0;
}

uint32_t MDdataWordBM::GetAmplitudeId() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & AmplitudeIdMask ) >> AmplitudeIdShift );
  return 0;
}

uint32_t MDdataWordBM::GetAmplitude() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & AmplitudeMask ) >> AmplitudeShift );
  return 0;
}

uint32_t MDdataWordBM::GetHumidity() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & HumidityMask ) >> HumidityShift );
  return 0;
}

uint32_t MDdataWordBM::GetTemperature() {
  if (IsValid())  return ( (*(uint32_t*)(_data) & TemperatureMask ) >> TemperatureShift );
  return 0;
}

void MDdataWordBM::Dump() {
  cout << *this;
}

ostream & operator<<(ostream &s, MDdataWordBM &dw) {
  uint32_t dt= dw.GetDataType();
  s << " BM FEB ";
  switch (dt) {
  case MDdataWordBM::SpillHeader:
    s << "Spill Header  BoardId: " << dw.GetBoardId()
      << "  Spill Tag: " << dw.GetSpillTag();
    break;

  case MDdataWordBM::TrigHeader:
    s << "Trigger Header  Gl. Trigger Tag: " << dw.GetTriggerTag();
    break;

  case MDdataWordBM::TimeMeas:
    s << "Channel: " << dw.GetChannelId();

    if ( dw.GetEdgeId() ) s << "  Time (RE): ";
    else s << "  Time (FE): ";

    s << dw.GetTriggerTime()
      << "  HitId: " << dw.GetHitId();
    break;

  case MDdataWordBM::ChargeMeas:
    s << "Channel: " << dw.GetChannelId()
      << "  Charge: " << dw.GetAmplitude()
      << "  HitId: " << dw.GetHitId()
      << "  Amplitude Id: " << dw.GetAmplitudeId();
    break;

  case MDdataWordBM::TrigTrailer1:
    s << "Trigger Trailer  Gl. Trigger Tag: " << dw.GetTriggerTag();
    break;

  case MDdataWordBM::TrigTrailer2:
    s << "Trigger Trailer  Hit count: " << dw.GetHitCount()
      << "  Trigger Time: " << dw.GetTriggerTime();
    break;

  case MDdataWordBM::SpillTrailer1:
    s << "Spill Trailer1  BoardId: " << dw.GetBoardId();
    if (dw.GetEdgeId()==0)
      s << "  Spill Tag: " << dw.GetSpillTag();
    else
      s << "  Temperature: " << dw.GetTemperature() << "  Humidity: " << dw.GetHumidity();

    break;

  case MDdataWordBM::SpillTrailer2:
    s << "Spill Trailer2 Spill time: " << dw.GetSpillTime();
    break;

  default:
    s << "Unknown data word (" << *(dw.GetDataPtr()) << ")\n";
    break;
  }

  return s;
}
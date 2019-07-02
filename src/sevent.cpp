#include "sevent.h"

//Response class

Response::Response(qlonglong cnt, qlonglong ofst, qlonglong state, bool succ, QString msg) {
    count = cnt;
    offset = ofst;
    status = state;
    success = succ;
    message = msg;
}
Response::Response(QJsonObject dat) {
    count = dat["count"].toVariant().toLongLong();
    offset = dat["offset"].toVariant().toLongLong();
    status = dat["status"].toVariant().toLongLong();
    success = dat["success"].toBool();
    message = dat["message"].toString();
}

void Response::setCount(qlonglong cnt) {count = cnt;}
void Response::setOffset(qlonglong ofst) {offset = ofst;}
void Response::setStatus(qlonglong stat) {status = stat;}
void Response::setSuccess(bool succ) {success = succ;}
void Response::setMessage(QString msg) {message = msg;}

qlonglong Response::getCount() {return count;}
qlonglong Response::getOffset() {return offset;}
qlonglong Response::getStatus() {return status;}
bool Response::getSuccess() {return success;}
QString Response::getMessage() {return message;}


//Event Class

ServerEvent::ServerEvent(QString nam, QString dets, QString locn, QString stat) {
    created_at = 0;
    updated_at = 0;
    id = 0;
    owner_id = "";
    name = nam;
    details = dets;
    location = locn;
    status = stat;
}
ServerEvent::ServerEvent(QJsonObject dat) {
    created_at = dat["created_at"].toVariant().toLongLong();
    updated_at = dat["updated_at"].toVariant().toLongLong();
    id = dat["id"].toVariant().toLongLong();
    owner_id = dat["owner_id"].toString();
    name = dat["name"].toString();
    details = dat["details"].toString();
    location = dat["location"].toString();
    status = dat["status"].toString();
}

void ServerEvent::setDetails(QString dets) {details = dets;}
void ServerEvent::setLocation(QString locn) {location = locn;}
void ServerEvent::setName(QString nam) {name = nam;}
void ServerEvent::setStatus(QString stat) {status = stat;}

QString ServerEvent::getDetails() {return details;}
QString ServerEvent::getLocation() {return location;}
QString ServerEvent::getName() {return name;}
QString ServerEvent::getStatus() {return status;}
QString ServerEvent::getOwnerID() {return owner_id;}
qlonglong ServerEvent::getCreationTime() {return created_at;}
qlonglong ServerEvent::getUpdateTime() {return updated_at;}
qlonglong ServerEvent::getID() {return id;}


// Event Instance class

EventInstance::EventInstance(qlonglong evtid, qlonglong patrnid) {
    started_at = 0;
    ended_at = 0;
    event_id = evtid;
    pattern_id = patrnid;
}
EventInstance::EventInstance(QJsonObject dat) {
    started_at = dat["started_at"].toVariant().toLongLong();
    ended_at = dat["ended_at"].toVariant().toLongLong();
    event_id = dat["event_id"].toVariant().toLongLong();
    pattern_id = dat["pattern_id"].toVariant().toLongLong();
}

void EventInstance::setEventID(qlonglong evtid) {event_id = evtid;}
void EventInstance::setPatternID(qlonglong patrnid) {pattern_id = patrnid;}

qlonglong EventInstance::getStartTime() {return started_at;}
qlonglong EventInstance::getEndTime() {return ended_at;}
qlonglong EventInstance::getEventID() {return event_id;}
qlonglong EventInstance::getPatternID() {return pattern_id;}


//Event Pattern class

EventPattern::EventPattern(qlonglong dur, qlonglong start, qlonglong end, QString exrl, QString rrl, QString tzone) {
    created_at = 0;
    updated_at = 0;
    started_at = start;
    ended_at = end;
    duration = dur;
    id = 0;
    exrule = exrl;
    rrule = rrl;
    timezone = tzone;
};
EventPattern::EventPattern(QJsonObject dat) {
    created_at = dat["created_at"].toVariant().toLongLong();
    updated_at = dat["updated_at"].toVariant().toLongLong();
    started_at = dat["started_at"].toVariant().toLongLong();
    ended_at = dat["ended_at"].toVariant().toLongLong();
    id = dat["id"].toVariant().toLongLong();
    duration = dat["duration"].toVariant().toLongLong();
    exrule = dat["exrule"].toString();
    rrule = dat["rrule"].toString();
    timezone = dat["timezone"].toString();
}

void EventPattern::setExcRule(QString exrl) {exrule = exrl;}
void EventPattern::setRepRule(QString rrl) {rrule = rrl;}
void EventPattern::setTimeZone(QString tzone) {timezone = tzone;}
void EventPattern::setStartTime(qlonglong start) {started_at = start;}
void EventPattern::setEndTime(qlonglong end) {ended_at = end;}
void EventPattern::setDuration(qlonglong dur) {duration = dur;}

QString EventPattern::getExcRule() {return exrule;}
QString EventPattern::getRepRule() {return rrule;}
QString EventPattern::getTimeZone() {return timezone;}
qlonglong EventPattern::getStartTime() {return started_at;}
qlonglong EventPattern::getEndTime() {return ended_at;}
qlonglong EventPattern::getDuration() {return duration;}
qlonglong EventPattern::getCreationTime() {return created_at;}
qlonglong EventPattern::getUpdateTime() {return updated_at;}
qlonglong EventPattern::getID() {return id;}

template <class Evt> ResponseData<Evt>::ResponseData(qlonglong cnt, qlonglong ofst, qlonglong stat, bool succ, QString msg, QList<Evt*> dat) : Response(cnt, ofst, stat, succ, msg) {
    data = dat;
}
template <class Evt> ResponseData<Evt>::ResponseData(QJsonObject obj) : Response(obj) {

    QJsonArray data_arr = obj["data"].toArray();

    for (int i = 0; i > data_arr.count(); i++) {

        QJsonObject val = data_arr[i].toObject();
        Evt* evt = new Evt(val);
        data.append(evt);
    }
}

template <class Evt> void ResponseData<Evt>::setData(QList<Evt*> dat) {data = dat;}
template <class Evt> QList<Evt*> ResponseData<Evt>::getData() {return data;}

EventResponse::EventResponse(qlonglong cnt, qlonglong ofst, qlonglong stat, bool succ, QString msg, QList<ServerEvent*> dat) : ResponseData<ServerEvent>(cnt, ofst, stat, succ, msg, dat){};
EventResponse::EventResponse(QJsonObject obj) : ResponseData<ServerEvent>(obj){};

EventInstanceResponse::EventInstanceResponse(qlonglong cnt, qlonglong ofst, qlonglong stat, bool succ, QString msg, QList<EventInstance*> dat) : ResponseData<EventInstance>(cnt, ofst, stat, succ, msg, dat){};
EventInstanceResponse::EventInstanceResponse(QJsonObject obj) : ResponseData<EventInstance>(obj){};

EventPatternResponse::EventPatternResponse(qlonglong cnt, qlonglong ofst, qlonglong stat, bool succ, QString msg, QList<EventPattern*> dat) : ResponseData<EventPattern>(cnt, ofst, stat, succ, msg, dat){};
EventPatternResponse::EventPatternResponse(QJsonObject obj) : ResponseData<EventPattern>(obj){};

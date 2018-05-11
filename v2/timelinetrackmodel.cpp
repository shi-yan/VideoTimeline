#include "timelinetrackmodel.h" 
#include "mainwindow.h"    

#include <QScopedPointer>
#include <QApplication>
#include <qmath.h>
#include <QTimer> 

static const quintptr NO_PARENT_ID = quintptr(-1); 

namespace timeline {

	TimelineTracksModel::TimelineTracksModel(QObject *parent)
		: QAbstractItemModel(parent) {
		connect(this, SIGNAL(modified()), SLOT(adjustBackgroundDuration()));
	}

	TimelineTracksModel::~TimelineTracksModel() {

	}

	int TimelineTracksModel::rowCount(const QModelIndex &parent) const {
		//if (!m_tractor)
		//	return 0;
		//if (parent.isValid()) {
		//	if (parent.internalId() != NO_PARENT_ID)
		//		return 0;
		//	int i = m_trackList.at(parent.row()).mlt_index;
		//	QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//	if (track) {
		//		Mlt::Playlist playlist(*track);
		//		int n = playlist.count();
		//		//            LOG_DEBUG() << __FUNCTION__ << parent << i << n;
		//		return n;
		//	}
		//	else {
		//		return 0;
		//	}
		//}
		//return m_trackList.count();
	}

	int TimelineTracksModel::columnCount(const QModelIndex &parent) const
	{
		Q_UNUSED(parent);
		return 1;
	}

	QVariant TimelineTracksModel::data(const QModelIndex &index, int role) const
	{
		//if (!m_tractor || !index.isValid())
		//	return QVariant();
		//if (index.parent().isValid()) {
		//	// Get data for a clip.
		//	int i = m_trackList.at(index.internalId()).mlt_index;
		//	QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//	if (track) {
		//		Mlt::Playlist playlist(*track);
		//		//            LOG_DEBUG() << __FUNCTION__ << index.row();
		//		QScopedPointer<Mlt::ClipInfo> info(playlist.clip_info(index.row()));
		//		if (info)
		//			switch (role) {
		//			case NameRole: {
		//				QString result;
		//				if (info->producer && info->producer->is_valid())
		//					result = info->producer->get(kShotcutCaptionProperty);
		//				if (result.isNull())
		//					result = Util::baseName(QString::fromUtf8(info->resource));
		//				if (result == "<producer>" && info->producer && info->producer->is_valid())
		//					result = QString::fromUtf8(info->producer->get("mlt_service"));
		//				return result;
		//			}
		//			case ResourceRole:
		//			case Qt::DisplayRole: {
		//				QString result = QString::fromUtf8(info->resource);
		//				if (result == "<producer>" && info->producer
		//					&& info->producer->is_valid() && info->producer->get("mlt_service"))
		//					result = QString::fromUtf8(info->producer->get("mlt_service"));
		//				return result;
		//			}
		//			case ServiceRole:
		//				if (info->producer && info->producer->is_valid())
		//					return QString::fromUtf8(info->producer->get("mlt_service"));
		//				break;
		//			case IsBlankRole:
		//				return playlist.is_blank(index.row());
		//			case StartRole:
		//				return info->start;
		//			case DurationRole:
		//				return info->frame_count;
		//			case InPointRole:
		//				return info->frame_in;
		//			case OutPointRole:
		//				return info->frame_out;
		//			case FramerateRole:
		//				return info->fps;
		//			case IsAudioRole:
		//				return m_trackList[index.internalId()].type == AudioTrackType;
		//			case AudioLevelsRole:
		//				if (info->producer->get_data(kAudioLevelsProperty))
		//					return QVariant::fromValue(*((QVariantList*)info->producer->get_data(kAudioLevelsProperty)));
		//				else
		//					return QVariant();
		//			case FadeInRole: {
		//				QScopedPointer<Mlt::Filter> filter(getFilter("fadeInVolume", info->producer));
		//				if (!filter || !filter->is_valid())
		//					filter.reset(getFilter("fadeInBrightness", info->producer));
		//				if (!filter || !filter->is_valid())
		//					filter.reset(getFilter("fadeInMovit", info->producer));
		//				return (filter && filter->is_valid()) ? filter->get_length() : 0;
		//			}
		//			case FadeOutRole: {
		//				QScopedPointer<Mlt::Filter> filter(getFilter("fadeOutVolume", info->producer));
		//				if (!filter || !filter->is_valid())
		//					filter.reset(getFilter("fadeOutBrightness", info->producer));
		//				if (!filter || !filter->is_valid())
		//					filter.reset(getFilter("fadeOutMovit", info->producer));
		//				return (filter && filter->is_valid()) ? filter->get_length() : 0;
		//			}
		//			case IsTransitionRole:
		//				return isTransition(playlist, index.row());
		//			case FileHashRole:
		//				return MAIN.getHash(*info->producer);
		//			case SpeedRole: {
		//				double speed = 1.0;
		//				if (info->producer && info->producer->is_valid()) {
		//					if (!qstrcmp("timewarp", info->producer->get("mlt_service")))
		//						speed = info->producer->get_double("warp_speed");
		//				}
		//				return speed;
		//			}
		//			case IsFilteredRole:
		//				return isFiltered(info->producer);
		//			default:
		//				break;
		//			}
		//	}
		//}
		//else {
		//	// Get data for a track.
		//	int i = m_trackList.at(index.row()).mlt_index;
		//	QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//	if (track) {
		//		Mlt::Playlist playlist(*track);
		//		switch (role) {
		//		case NameRole:
		//		case Qt::DisplayRole:
		//			return track->get(kTrackNameProperty);
		//		case DurationRole:
		//			return playlist.get_playtime();
		//		case IsMuteRole:
		//			return playlist.get_int("hide") & 2;
		//		case IsHiddenRole:
		//			return playlist.get_int("hide") & 1;
		//		case IsAudioRole:
		//			return m_trackList[index.row()].type == AudioTrackType;
		//		case IsLockedRole:
		//			return track->get_int(kTrackLockProperty);
		//		case IsCompositeRole: {
		//			QScopedPointer<Mlt::Transition> transition(getTransition("frei0r.cairoblend", i));
		//			if (!transition)
		//				transition.reset(getTransition("movit.overlay", i));
		//			if (transition && transition->is_valid()) {
		//				if (!transition->get_int("disable"))
		//					return true;
		//			}
		//			return false;
		//		}
		//		case IsFilteredRole:
		//			return isFiltered(track.data());
		//		default:
		//			break;
		//		}
		//	}
		//}
		return QVariant();
	}

	QModelIndex TimelineTracksModel::index(int row, int column, const QModelIndex &parent) const
	{
		//if (column > 0)
		//	return QModelIndex();
		////    LOG_DEBUG() << __FUNCTION__ << row << column << parent;
		//QModelIndex result;
		//if (parent.isValid()) {
		//	int i = m_trackList.at(parent.row()).mlt_index;
		//	QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//	if (track) {
		//		Mlt::Playlist playlist((mlt_playlist)track->get_producer());
		//		if (row < playlist.count())
		//			result = createIndex(row, column, parent.row());
		//	}
		//}
		//else if (row < m_trackList.count()) {
		//	result = createIndex(row, column, NO_PARENT_ID);
		//}
		//return result;
	}

	QModelIndex TimelineTracksModel::makeIndex(int trackIndex, int clipIndex) const
	{
		return index(clipIndex, 0, index(trackIndex));
	}

	QModelIndex TimelineTracksModel::parent(const QModelIndex &index) const
	{
		//    LOG_DEBUG() << __FUNCTION__ << index;
		if (!index.isValid() || index.internalId() == NO_PARENT_ID)
			return QModelIndex();
		else
			return createIndex(index.internalId(), 0, NO_PARENT_ID);
	}
	
	// exposed to QML
	QHash<int, QByteArray> TimelineTracksModel::roleNames() const
	{
		QHash<int, QByteArray> roles;
		roles[NameRole] = "name";
		roles[SourceRole] = "source"; 
		roles[IsBlankRole] = "blank";
		roles[StartRole] = "start";
		roles[DurationRole] = "duration";
		roles[InPointRole] = "in";
		roles[OutPointRole] = "out"; 
		roles[IsAudioRole] = "audio";
		roles[AudioLevelsRole] = "audioLevels";   
		return roles;
	}

	void TimelineTracksModel::setTrackName(int row, const QString &value)
	{
		/*if (row < m_trackList.size()) {
			int i = m_trackList.at(row).mlt_index;
			QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
			if (track) {
				track->set(kTrackNameProperty, value.toUtf8().constData());

				QModelIndex modelIndex = index(row, 0);
				QVector<int> roles;
				roles << NameRole;
				emit dataChanged(modelIndex, modelIndex, roles);
				emit modified();
			}
		}*/
	}

	void TimelineTracksModel::setTrackMute(int row, bool mute)
	{
		/*if (row < m_trackList.size()) {
			int i = m_trackList.at(row).mlt_index;
			QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
			if (track) {
				int hide = track->get_int("hide");
				if (mute)
					hide |= 2;
				else
					hide ^= 2;
				track->set("hide", hide);

				QModelIndex modelIndex = index(row, 0);
				QVector<int> roles;
				roles << IsMuteRole;
				emit dataChanged(modelIndex, modelIndex, roles);
				emit modified();
			}
		}*/
	}  

	void TimelineTracksModel::setTrackLock(int row, bool lock)
	{
		/*if (row < m_trackList.size()) {
			int i = m_trackList.at(row).mlt_index;
			QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
			track->set(kTrackLockProperty, lock);

			QModelIndex modelIndex = index(row, 0);
			QVector<int> roles;
			roles << IsLockedRole;
			emit dataChanged(modelIndex, modelIndex, roles);
			emit modified();
		}*/
	}

	bool TimelineTracksModel::trimClipInValid(int trackIndex, int clipIndex, int delta, bool ripple) {
		/*bool result = true;
		int i = m_trackList.at(trackIndex).mlt_index;
		QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		if (track) {
			Mlt::Playlist playlist(*track);
			QScopedPointer<Mlt::ClipInfo> info(playlist.clip_info(clipIndex));

			if (!info || (info->frame_in + delta) < 0 || (info->frame_in + delta) > info->frame_out)
				result = false;
			else if (delta < 0 && clipIndex <= 0)
				result = false;
			else if (!ripple && delta < 0 && clipIndex > 0 && !playlist.is_blank(clipIndex - 1))
				result = false;
			else if (delta > 0 && clipIndex > 0 && isTransition(playlist, clipIndex - 1))
				result = false;
		}
		return result;*/
	}

	int TimelineTracksModel::trimClipIn(int trackIndex, int clipIndex, int delta, bool ripple) {
		//int result = clipIndex;
		//QList<int> tracksToRemoveRegionFrom;
		//int whereToRemoveRegion = -1;

		//for (int i = 0; i < m_trackList.count(); ++i) {
		//	int mltIndex = m_trackList.at(i).mlt_index;
		//	QScopedPointer<Mlt::Producer> track(m_tractor->track(mltIndex));
		//	if (!track)
		//		continue;

		//	//when not rippling, never touch the other tracks
		//	if (trackIndex != i && (!ripple || !Settings.timelineRippleAllTracks()))
		//		continue;

		//	if (Settings.timelineRippleAllTracks()) {
		//		if (track->get_int(kTrackLockProperty))
		//			continue;

		//		if (trackIndex != i && ripple) {
		//			tracksToRemoveRegionFrom << i;
		//			continue;
		//		}
		//	}

		//	Mlt::Playlist playlist(*track);
		//	QScopedPointer<Mlt::ClipInfo> info(playlist.clip_info(clipIndex));

		//	Q_ASSERT(whereToRemoveRegion == -1);
		//	whereToRemoveRegion = info->start + delta;

		//	if (info->frame_in + delta < 0)
		//		delta = -info->frame_in; // clamp

		//	int in = info->frame_in + delta;
		//	int out = info->frame_out;
		//	playlist.resize_clip(clipIndex, in, out);

		//	// Adjust all filters that have an explicit duration.
		//	int n = info->producer->filter_count();
		//	for (int j = 0; j < n; j++) {
		//		Mlt::Filter* filter = info->producer->filter(j);
		//		if (filter && filter->is_valid() && filter->get_length() > 0) {
		//			if (QString(filter->get(kShotcutFilterProperty)).startsWith("fadeIn")
		//				|| QString(filter->get("mlt_service")) == "webvfx") {
		//				filter->set_in_and_out(in, in + filter->get_length() - 1);
		//			}
		//		}
		//		delete filter;
		//	}

		//	QModelIndex modelIndex = createIndex(clipIndex, 0, i);
		//	QVector<int> roles;
		//	roles << DurationRole;
		//	roles << InPointRole;
		//	emit dataChanged(modelIndex, modelIndex, roles);

		//	if (!ripple) {
		//		// Adjust left of the clip.
		//		if (clipIndex > 0 && playlist.is_blank(clipIndex - 1)) {
		//			int out = playlist.clip_length(clipIndex - 1) + delta - 1;
		//			if (out < 0) {
		//				//                LOG_DEBUG() << "remove blank at left";
		//				beginRemoveRows(index(i), clipIndex - 1, clipIndex - 1);
		//				playlist.remove(clipIndex - 1);
		//				endRemoveRows();
		//				--result;
		//			}
		//			else {
		//				//                LOG_DEBUG() << "adjust blank on left to" << out;
		//				playlist.resize_clip(clipIndex - 1, 0, out);

		//				QModelIndex index = createIndex(clipIndex - 1, 0, i);
		//				QVector<int> roles;
		//				roles << DurationRole;
		//				emit dataChanged(index, index, roles);
		//			}
		//		}
		//		else if (delta > 0) {
		//			//            LOG_DEBUG() << "add blank on left duration" << delta - 1;
		//			beginInsertRows(index(i), clipIndex, clipIndex);
		//			playlist.insert_blank(clipIndex, delta - 1);
		//			endInsertRows();
		//			++result;
		//		}
		//	}
		//	emit modified();
		//}
		//foreach(int idx, tracksToRemoveRegionFrom) {
		//	Q_ASSERT(whereToRemoveRegion != -1);
		//	removeRegion(idx, whereToRemoveRegion - delta, delta);
		//}
		//return result;
	}

	void TimelineTracksModel::notifyClipIn(int trackIndex, int clipIndex) {
		/*if (trackIndex >= 0 && trackIndex < m_trackList.size() && clipIndex >= 0) {
			QModelIndex index = createIndex(clipIndex, 0, trackIndex);
			QVector<int> roles;
			roles << AudioLevelsRole;
			emit dataChanged(index, index, roles);
			MLT.refreshConsumer();
		}
		m_isMakingTransition = false;*/
	}

	bool TimelineTracksModel::trimClipOutValid(int trackIndex, int clipIndex, int delta, bool ripple) {
	/*	bool result = true;
		int i = m_trackList.at(trackIndex).mlt_index;
		QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		if (track) {
			Mlt::Playlist playlist(*track);
			QScopedPointer<Mlt::ClipInfo> info(playlist.clip_info(clipIndex));
			if (!info || (info->frame_out - delta) >= info->length || (info->frame_out - delta) < info->frame_in)
				result = false;
			else if (!ripple && delta < 0 && (clipIndex + 1) < playlist.count() && !playlist.is_blank(clipIndex + 1))
				result = false;
			else if (delta > 0 && (clipIndex + 1) < playlist.count() && isTransition(playlist, clipIndex + 1))
				return false;
		}
		return result;*/
	}

	int TimelineTracksModel::trackHeight() const {
		/*	int result = m_tractor ? m_tractor->get_int(kTrackHeightProperty) : 50;
			return result ? result : 50;*/
	}

	void TimelineTracksModel::setTrackHeight(int height) {
		/*if (m_tractor) {
			m_tractor->set(kTrackHeightProperty, height);
			emit trackHeightChanged();
		}*/
	}

	double TimelineTracksModel::scaleFactor() const {
		/*double result = m_tractor ? m_tractor->get_double(kTimelineScaleProperty) : 0;
		return (result > 0) ? result : (qPow(1.0, 3.0) + 0.01);*/
	}

	void TimelineTracksModel::setScaleFactor(double scale) {
		/*if (m_tractor) {
			m_tractor->set(kTimelineScaleProperty, scale);
			emit scaleFactorChanged();
		}*/
	}

	int TimelineTracksModel::trimClipOut(int trackIndex, int clipIndex, int delta, bool ripple) {
		//QList<int> tracksToRemoveRegionFrom;
		//int result = clipIndex;
		//int whereToRemoveRegion = -1;

		//for (int i = 0; i < m_trackList.count(); ++i) {
		//	int mltIndex = m_trackList.at(i).mlt_index;
		//	QScopedPointer<Mlt::Producer> track(m_tractor->track(mltIndex));
		//	if (!track)
		//		continue;

		//	Mlt::Playlist playlist(*track);
		//	QScopedPointer<Mlt::ClipInfo> info(playlist.clip_info(clipIndex));

		//	//when not rippling, never touch the other tracks
		//	if (trackIndex != i && (!ripple || !Settings.timelineRippleAllTracks()))
		//		continue;

		//	if (Settings.timelineRippleAllTracks()) {
		//		if (track->get_int(kTrackLockProperty))
		//			continue;

		//		if (trackIndex != i && ripple) {
		//			tracksToRemoveRegionFrom << i;
		//			continue;
		//		}
		//	}

		//	Q_ASSERT(whereToRemoveRegion == -1);
		//	whereToRemoveRegion = info->start + info->frame_count - delta;

		//	if ((info->frame_out - delta) >= info->length)
		//		delta = info->frame_out - info->length + 1; // clamp

		//	if (!ripple) {
		//		// Adjust right of the clip.
		//		if (clipIndex >= 0 && (clipIndex + 1) < playlist.count() && playlist.is_blank(clipIndex + 1)) {
		//			int out = playlist.clip_length(clipIndex + 1) + delta - 1;
		//			if (out < 0) {
		//				//                LOG_DEBUG() << "remove blank at right";
		//				beginRemoveRows(index(i), clipIndex + 1, clipIndex + 1);
		//				playlist.remove(clipIndex + 1);
		//				endRemoveRows();
		//			}
		//			else {
		//				//                LOG_DEBUG() << "adjust blank on right to" << out;
		//				playlist.resize_clip(clipIndex + 1, 0, out);

		//				QModelIndex index = createIndex(clipIndex + 1, 0, i);
		//				QVector<int> roles;
		//				roles << DurationRole;
		//				emit dataChanged(index, index, roles);
		//			}
		//		}
		//		else if (delta > 0 && (clipIndex + 1) < playlist.count()) {
		//			// Add blank to right.
		//			//            LOG_DEBUG() << "add blank on right duration" << (delta - 1);
		//			int newIndex = clipIndex + 1;
		//			beginInsertRows(index(i), newIndex, newIndex);
		//			playlist.insert_blank(newIndex, delta - 1);
		//			endInsertRows();
		//		}
		//	}
		//	int in = info->frame_in;
		//	int out = info->frame_out - delta;
		//	playlist.resize_clip(clipIndex, in, out);

		//	// Adjust all filters that have an explicit duration.
		//	int n = info->producer->filter_count();
		//	for (int j = 0; j < n; j++) {
		//		Mlt::Filter* filter = info->producer->filter(j);
		//		if (filter && filter->is_valid() && filter->get_length() > 0) {
		//			if (QString(filter->get(kShotcutFilterProperty)).startsWith("fadeOut")
		//				|| QString(filter->get("mlt_service")) == "webvfx") {
		//				filter->set_in_and_out(out - filter->get_length() + 1, out);
		//			}
		//		}
		//		delete filter;
		//	}

		//	QModelIndex index = createIndex(clipIndex, 0, i);
		//	QVector<int> roles;
		//	roles << DurationRole;
		//	roles << OutPointRole;
		//	emit dataChanged(index, index, roles);
		//	emit modified();
		//}
		//foreach(int idx, tracksToRemoveRegionFrom) {
		//	Q_ASSERT(whereToRemoveRegion != -1);
		//	removeRegion(idx, whereToRemoveRegion, delta);
		//}
		//return result;
	}

	void TimelineTracksModel::notifyClipOut(int trackIndex, int clipIndex) {
	/*	if (trackIndex >= 0 && trackIndex < m_trackList.size() && clipIndex >= 0) {
			QModelIndex index = createIndex(clipIndex, 0, trackIndex);
			QVector<int> roles;
			roles << AudioLevelsRole;
			emit dataChanged(index, index, roles);
			MLT.refreshConsumer();
		}
		m_isMakingTransition = false;*/
	}

	bool TimelineTracksModel::moveClipValid(int fromTrack, int toTrack, int clipIndex, int position) {
		//// XXX This is very redundant with moveClip().
		//bool result = false;
		//int i = m_trackList.at(toTrack).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	int targetIndex = playlist.get_clip_index_at(position);

		//	if (fromTrack != toTrack) {
		//		Mlt::Producer* trackFrom = m_tractor->track(m_trackList.at(fromTrack).mlt_index);
		//		Mlt::Playlist playlistFrom(*trackFrom);
		//		delete trackFrom;
		//		if (clipIndex < 0 || clipIndex >= playlistFrom.count())
		//			return false;
		//		QScopedPointer<Mlt::Producer> clip(playlistFrom.get_clip(clipIndex));
		//		if (position >= playlist.get_playtime())
		//			result = true;
		//		else if (playlist.is_blank_at(0) && playlist.count() == 1)
		//			// blank track
		//			result = true;
		//		else if (playlist.is_blank_at(position) && playlist.is_blank_at(position + clip->get_playtime() - 1)
		//			&& playlist.get_clip_index_at(position) == playlist.get_clip_index_at(position + clip->get_playtime() - 1))
		//			result = true;
		//		if (!result) {
		//			QModelIndex parentIndex = index(fromTrack);
		//			// Remove blank on fromTrack.
		//			beginRemoveRows(parentIndex, clipIndex, clipIndex);
		//			playlistFrom.remove(clipIndex);
		//			endRemoveRows();

		//			// Insert clip on fromTrack.
		//			beginInsertRows(parentIndex, clipIndex, clipIndex);
		//			playlistFrom.insert(*clip, clipIndex, clip->get_in(), clip->get_out());
		//			endInsertRows();
		//		}
		//	}
		//	else if ((clipIndex + 1) < playlist.count() && position >= playlist.get_playtime()) {
		//		result = true;
		//	}
		//	else if ((targetIndex < (clipIndex - 1) || targetIndex >(clipIndex + 1))
		//		&& playlist.is_blank_at(position) && playlist.clip_length(clipIndex) <= playlist.clip_length(targetIndex)) {
		//		result = true;
		//	}
		//	else if (targetIndex >= (clipIndex - 1) && targetIndex <= (clipIndex + 1)) {
		//		int length = playlist.clip_length(clipIndex);
		//		int targetIndexEnd = playlist.get_clip_index_at(position + length - 1);

		//		if ((playlist.is_blank_at(position) || targetIndex == clipIndex)
		//			&& (playlist.is_blank_at(position + length - 1) || targetIndexEnd == clipIndex)) {

		//			result = true;
		//		}
		//	}
		//}
		//return result;
	}

	bool TimelineTracksModel::moveClip(int fromTrack, int toTrack, int clipIndex, int position) { 
		//bool result = false;
		//int i = m_trackList.at(toTrack).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	int targetIndex = playlist.get_clip_index_at(position);

		//	if (fromTrack != toTrack) {
		//		result = moveClipToTrack(fromTrack, toTrack, clipIndex, position);
		//	}
		//	else if ((clipIndex + 1) < playlist.count() && position >= playlist.get_playtime()) {
		//		// Clip relocated to end of playlist.
		//		moveClipToEnd(playlist, toTrack, clipIndex, position);
		//		result = true;
		//	}
		//	else if ((targetIndex < (clipIndex - 1) || targetIndex >(clipIndex + 1))
		//		&& playlist.is_blank_at(position) && playlist.clip_length(clipIndex) <= playlist.clip_length(targetIndex)) {
		//		// Relocate clip.
		//		relocateClip(playlist, toTrack, clipIndex, position);
		//		result = true;
		//	}
		//	else if (targetIndex >= (clipIndex - 1) && targetIndex <= (clipIndex + 1)) {
		//		int length = playlist.clip_length(clipIndex);
		//		int targetIndexEnd = playlist.get_clip_index_at(position + length - 1);

		//		if ((playlist.is_blank_at(position) || targetIndex == clipIndex)
		//			&& (playlist.is_blank_at(position + length - 1) || targetIndexEnd == clipIndex)) {

		//			if (position < 0) {
		//				// Special case: dragged left of timeline origin.
		//				Mlt::ClipInfo* info = playlist.clip_info(clipIndex);
		//				playlist.resize_clip(clipIndex, info->frame_in - position, info->frame_out);
		//				delete info;
		//				QModelIndex idx = createIndex(clipIndex, 0, toTrack);
		//				QVector<int> roles;
		//				roles << DurationRole;
		//				roles << InPointRole;
		//				emit dataChanged(idx, idx, roles);
		//				if (clipIndex > 0) {
		//					QModelIndex parentIndex = index(toTrack);
		//					beginMoveRows(parentIndex, clipIndex, clipIndex, parentIndex, 0);
		//					playlist.move(clipIndex, 0);
		//					endMoveRows();
		//					consolidateBlanks(playlist, toTrack);
		//					clipIndex = 0;
		//				}
		//			}
		//			// Reposition the clip within its current blank spot.
		//			moveClipInBlank(playlist, toTrack, clipIndex, position);
		//			result = true;
		//		}
		//	}
		//}
		//if (result) {
		//	emit modified();
		//	MLT.refreshConsumer();
		//}
		//return result;
	}

	int TimelineTracksModel::overwriteClip(int trackIndex,int position, bool seek) {
		//createIfNeeded();
		//int result = -1;
		//int i = m_trackList.at(trackIndex).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	if (position >= playlist.get_playtime() - 1) {
		//		//            LOG_DEBUG() << __FUNCTION__ << "appending";
		//		removeBlankPlaceholder(playlist, trackIndex);
		//		int n = playlist.count();
		//		int length = position - playlist.clip_start(n - 1) - playlist.clip_length(n - 1);

		//		// Add blank to end if needed.
		//		if (length > 0) {
		//			beginInsertRows(index(trackIndex), n, n);
		//			playlist.blank(length - 1);
		//			endInsertRows();
		//			++n;
		//		}

		//		// Append clip.
		//		int in = clip.get_in();
		//		int out = clip.get_out();
		//		clip.set_in_and_out(0, clip.get_length() - 1);
		//		beginInsertRows(index(trackIndex), n, n);
		//		playlist.append(clip.parent(), in, out);
		//		endInsertRows();
		//		AudioLevelsTask::start(clip.parent(), this, createIndex(n, 0, trackIndex));
		//		result = playlist.count() - 1;
		//	}
		//	else if (position + clip.get_playtime() > playlist.get_playtime()
		//		// Handle straddling - new clip larger than another with blanks on both sides.
		//		|| playlist.get_clip_index_at(position) == playlist.get_clip_index_at(position + clip.get_playtime() - 1)) {
		//		//            LOG_DEBUG() << __FUNCTION__ << "overwriting blank space" << clip.get_playtime();
		//		int targetIndex = playlist.get_clip_index_at(position);

		//		if (position > playlist.clip_start(targetIndex)) {
		//			splitClip(trackIndex, targetIndex, position);

		//			// Notify item on left was adjusted.
		//			QModelIndex modelIndex = createIndex(targetIndex, 0, trackIndex);
		//			QVector<int> roles;
		//			roles << DurationRole;
		//			emit dataChanged(modelIndex, modelIndex, roles);
		//			AudioLevelsTask::start(clip.parent(), this, modelIndex);
		//			++targetIndex;
		//		}
		//		else if (position < 0) {
		//			clip.set_in_and_out(-position, clip.get_out());
		//			QModelIndex modelIndex = createIndex(targetIndex, 0, trackIndex);
		//			// Notify clip on right was adjusted.
		//			QVector<int> roles;
		//			roles << InPointRole;
		//			roles << DurationRole;
		//			emit dataChanged(modelIndex, modelIndex, roles);
		//		}

		//		// Adjust clip on right.
		//		int duration = playlist.clip_length(targetIndex) - clip.get_playtime();
		//		if (duration > 0) {
		//			//                LOG_DEBUG() << "adjust item on right" << (targetIndex) << " to" << duration;
		//			playlist.resize_clip(targetIndex, 0, duration - 1);
		//			QModelIndex modelIndex = createIndex(targetIndex, 0, trackIndex);
		//			// Notify clip on right was adjusted.
		//			QVector<int> roles;
		//			roles << DurationRole;
		//			emit dataChanged(modelIndex, modelIndex, roles);
		//			AudioLevelsTask::start(clip.parent(), this, modelIndex);
		//		}
		//		else {
		//			//                LOG_DEBUG() << "remove item on right";
		//			beginRemoveRows(index(trackIndex), targetIndex, targetIndex);
		//			playlist.remove(targetIndex);
		//			endRemoveRows();
		//		}
		//		// Insert clip between subclips.
		//		int in = clip.get_in();
		//		int out = clip.get_out();
		//		clip.set_in_and_out(0, clip.get_length() - 1);
		//		beginInsertRows(index(trackIndex), targetIndex, targetIndex);
		//		playlist.insert(clip.parent(), targetIndex, in, out);
		//		endInsertRows();
		//		result = targetIndex;
		//	}
		//	if (result >= 0) {
		//		QModelIndex index = createIndex(result, 0, trackIndex);
		//		AudioLevelsTask::start(clip.parent(), this, index);
		//		emit modified();
		//		if (seek)
		//			emit seeked(playlist.clip_start(result) + playlist.clip_length(result));
		//	}
		//}
		//return result;
	}

	QString TimelineTracksModel::overwrite(int trackIndex, int position, bool seek) {
		//createIfNeeded();
		//Mlt::Playlist result;
		//int i = m_trackList.at(trackIndex).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	removeBlankPlaceholder(playlist, trackIndex);
		//	int targetIndex = playlist.get_clip_index_at(position);
		//	if (position >= playlist.get_playtime() - 1) {
		//		//            LOG_DEBUG() << __FUNCTION__ << "appending";
		//		int n = playlist.count();
		//		int length = position - playlist.clip_start(n - 1) - playlist.clip_length(n - 1);

		//		// Add blank to end if needed.
		//		if (length > 0) {
		//			beginInsertRows(index(trackIndex), n, n);
		//			playlist.blank(length - 1);
		//			endInsertRows();
		//			++n;
		//		}

		//		// Append clip.
		//		int in = clip.get_in();
		//		int out = clip.get_out();
		//		clip.set_in_and_out(0, clip.get_length() - 1);
		//		beginInsertRows(index(trackIndex), n, n);
		//		playlist.append(clip.parent(), in, out);
		//		endInsertRows();
		//		targetIndex = playlist.count() - 1;
		//	}
		//	else {
		//		int lastIndex = playlist.get_clip_index_at(position + clip.get_playtime());
		//		//            LOG_DEBUG() << __FUNCTION__ << "overwriting with duration" << clip.get_playtime()
		//		//                << "from" << targetIndex << "to" << lastIndex;

		//		// Add affected clips to result playlist.
		//		int i = targetIndex;
		//		if (position == playlist.clip_start(targetIndex))
		//			--i;
		//		for (; i <= lastIndex; i++) {
		//			Mlt::Producer* producer = playlist.get_clip(i);
		//			if (producer)
		//				result.append(*producer);
		//			delete producer;
		//		}

		//		if (position > playlist.clip_start(targetIndex)) {
		//			//                LOG_DEBUG() << "split starting item" <<  targetIndex;
		//			splitClip(trackIndex, targetIndex, position);
		//			++targetIndex;
		//		}
		//		else if (position < 0) {
		//			clip.set_in_and_out(-position, clip.get_out());
		//			QModelIndex modelIndex = createIndex(targetIndex, 0, trackIndex);
		//			// Notify clip was adjusted.
		//			QVector<int> roles;
		//			roles << InPointRole;
		//			roles << DurationRole;
		//			emit dataChanged(modelIndex, modelIndex, roles);
		//		}

		//		int length = clip.get_playtime();
		//		while (length > 0 && targetIndex < playlist.count()) {
		//			if (playlist.clip_length(targetIndex) > length) {
		//				//                    LOG_DEBUG() << "split last item" << targetIndex;
		//				splitClip(trackIndex, targetIndex, position + length);
		//			}
		//			//                LOG_DEBUG() << "length" << length << "item length" << playlist.clip_length(targetIndex);
		//			length -= playlist.clip_length(targetIndex);
		//			//                LOG_DEBUG() << "delete item" << targetIndex;
		//			beginRemoveRows(index(trackIndex), targetIndex, targetIndex);
		//			playlist.remove(targetIndex);
		//			endRemoveRows();
		//		}

		//		// Insert clip between subclips.
		//		int in = clip.get_in();
		//		int out = clip.get_out();
		//		clip.set_in_and_out(0, clip.get_length() - 1);
		//		beginInsertRows(index(trackIndex), targetIndex, targetIndex);
		//		playlist.insert(clip.parent(), targetIndex, in, out);
		//		endInsertRows();
		//	}
		//	QModelIndex index = createIndex(targetIndex, 0, trackIndex);
		//	AudioLevelsTask::start(clip.parent(), this, index);
		//	emit modified();
		//	if (seek)
		//		emit seeked(playlist.clip_start(targetIndex) + playlist.clip_length(targetIndex));
		//}
		//return MLT.XML(&result);
	}

	int TimelineTracksModel::insertClip(int trackIndex, int position) {
		//createIfNeeded();
		//int result = -1;
		//int i = m_trackList.at(trackIndex).mlt_index;
		//int clipPlaytime = clip.get_playtime();
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	if (position < 0 || position >= playlist.get_playtime() - 1) {
		//		//            LOG_DEBUG() << __FUNCTION__ << "appending";
		//		removeBlankPlaceholder(playlist, trackIndex);
		//		int n = playlist.count();
		//		int length = position - playlist.clip_start(n - 1) - playlist.clip_length(n - 1);

		//		// Add blank to end if needed.
		//		if (length > 0) {
		//			beginInsertRows(index(trackIndex), n, n);
		//			playlist.blank(length - 1);
		//			endInsertRows();
		//			++n;
		//		}

		//		// Append clip.
		//		int in = clip.get_in();
		//		int out = clip.get_out();
		//		clip.set_in_and_out(0, clip.get_length() - 1);
		//		beginInsertRows(index(trackIndex), n, n);
		//		playlist.append(clip.parent(), in, out);
		//		endInsertRows();
		//		result = playlist.count() - 1;
		//	}
		//	else {
		//		//            LOG_DEBUG() << __FUNCTION__ << "inserting" << position << MLT.XML(&clip);
		//		int targetIndex = playlist.get_clip_index_at(position);

		//		if (position > playlist.clip_start(targetIndex)) {
		//			splitClip(trackIndex, targetIndex, position);

		//			// Notify item on left was adjusted.
		//			QModelIndex modelIndex = createIndex(targetIndex, 0, trackIndex);
		//			QVector<int> roles;
		//			roles << DurationRole;
		//			emit dataChanged(modelIndex, modelIndex, roles);
		//			AudioLevelsTask::start(clip.parent(), this, modelIndex);
		//			++targetIndex;

		//			// Notify item on right was adjusted.
		//			modelIndex = createIndex(targetIndex, 0, trackIndex);
		//			emit dataChanged(modelIndex, modelIndex, roles);
		//			AudioLevelsTask::start(clip.parent(), this, modelIndex);
		//		}

		//		// Insert clip between split blanks.
		//		beginInsertRows(index(trackIndex), targetIndex, targetIndex);
		//		if (qstrcmp("blank", clip.get("mlt_service"))) {
		//			int in = clip.get_in();
		//			int out = clip.get_out();
		//			clip.set_in_and_out(0, clip.get_length() - 1);
		//			playlist.insert(clip.parent(), targetIndex, in, out);
		//		}
		//		else {
		//			playlist.insert_blank(targetIndex, clipPlaytime - 1);
		//		}
		//		endInsertRows();
		//		result = targetIndex;
		//	}
		//	if (result >= 0) {
		//		if (Settings.timelineRippleAllTracks()) {
		//			//fill in/expand blanks in all the other tracks
		//			QList<int> tracksToInsertBlankInto;
		//			for (int j = 0; j < m_trackList.count(); ++j) {
		//				if (j == trackIndex)
		//					continue;
		//				int mltIndex = m_trackList.at(j).mlt_index;
		//				QScopedPointer<Mlt::Producer> otherTrack(m_tractor->track(mltIndex));
		//				if (otherTrack->get_int(kTrackLockProperty))
		//					continue;

		//				tracksToInsertBlankInto << j;
		//			}
		//			if (!tracksToInsertBlankInto.isEmpty())
		//				insertOrAdjustBlankAt(tracksToInsertBlankInto, position, clipPlaytime);
		//		}

		//		QModelIndex index = createIndex(result, 0, trackIndex);
		//		AudioLevelsTask::start(clip.parent(), this, index);
		//		emit modified();
		//		emit seeked(playlist.clip_start(result) + playlist.clip_length(result));
		//	}
		//}
		//return result;
	}

	int TimelineTracksModel::appendClip(int trackIndex) {
	/*	if (!createIfNeeded()) {
			return -1;
		}
		int i = m_trackList.at(trackIndex).mlt_index;
		QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		if (track) {
			Mlt::Playlist playlist(*track);
			removeBlankPlaceholder(playlist, trackIndex);
			i = playlist.count();
			int in = clip.get_in();
			int out = clip.get_out();
			clip.set_in_and_out(0, clip.get_length() - 1);
			beginInsertRows(index(trackIndex), i, i);
			playlist.append(clip.parent(), in, out);
			endInsertRows();
			QModelIndex index = createIndex(i, 0, trackIndex);
			AudioLevelsTask::start(clip.parent(), this, index);
			emit modified();
			emit seeked(playlist.clip_start(i) + playlist.clip_length(i));
			return i;
		}
		return -1;*/
	}

	void TimelineTracksModel::removeClip(int trackIndex, int clipIndex) {
//		int i = m_trackList.at(trackIndex).mlt_index;
//		QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
//		int clipPlaytime = -1;
//		int clipStart = -1;
//
//		if (track) {
//			Mlt::Playlist playlist(*track);
//			if (clipIndex < playlist.count()) {
//				// Shotcut does not like the behavior of remove() on a
//				// transition (MLT mix clip). So, we null mlt_mix to prevent it.
//				clearMixReferences(trackIndex, clipIndex);
//
//				QScopedPointer<Mlt::Producer> producer(playlist.get_clip(clipIndex));
//				if (producer) {
//					clipPlaytime = producer->get_playtime();
//					clipStart = playlist.clip_start(clipIndex);
//				}
//
//#ifdef Q_OS_MAC
//				// XXX Remove this when Qt is upgraded to > 5.2.
//				// Workaround a crash bug choosing Remove from CLip/blank context menu.
//				playlist.remove(clipIndex);
//				// Consolidate blanks
//				for (int i = 1; i < playlist.count(); i++) {
//					if (playlist.is_blank(i - 1) && playlist.is_blank(i)) {
//						int out = playlist.clip_length(i - 1) + playlist.clip_length(i) - 1;
//						playlist.resize_clip(i - 1, 0, out);
//						QModelIndex idx = createIndex(i - 1, 0, trackIndex);
//						QVector<int> roles;
//						roles << DurationRole;
//						emit dataChanged(idx, idx, roles);
//						playlist.remove(i--);
//					}
//					if (playlist.count() > 0) {
//						int i = playlist.count() - 1;
//						if (playlist.is_blank(i)) {
//							playlist.remove(i);
//						}
//					}
//		}
//				if (playlist.count() == 0) {
//					playlist.blank(0);
//				}
//				QTimer::singleShot(10, this, SLOT(reload()));
//#else
//				beginRemoveRows(index(trackIndex), clipIndex, clipIndex);
//				playlist.remove(clipIndex);
//				endRemoveRows();
//				consolidateBlanks(playlist, trackIndex);
//#endif
//				// Ripple all unlocked tracks.
//				if (clipPlaytime > 0 && Settings.timelineRippleAllTracks())
//					for (int j = 0; j < m_trackList.count(); ++j) {
//						if (j == trackIndex)
//							continue;
//
//						int mltIndex = m_trackList.at(j).mlt_index;
//						QScopedPointer<Mlt::Producer> otherTrack(m_tractor->track(mltIndex));
//						if (otherTrack) {
//							if (otherTrack->get_int(kTrackLockProperty))
//								continue;
//
//							removeRegion(j, clipStart, clipPlaytime);
//						}
//					}
//				emit modified();
//	}
//}
	}

	void TimelineTracksModel::splitClip(int trackIndex, int clipIndex, int position) {
		//int i = m_trackList.at(trackIndex).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	QScopedPointer<Mlt::Producer> clip(playlist.get_clip(clipIndex));

		//	// Make copy of clip.
		//	Mlt::Producer producer(MLT.profile(), "xml-string",
		//		MLT.XML(&clip->parent()).toUtf8().constData());
		//	int in = clip->get_in();
		//	int out = clip->get_out();
		//	int duration = position - playlist.clip_start(clipIndex);

		//	// If this clip has a transition on the right.
		//	if (clip->get_data("mix_out")) {
		//		// Remove fades that are usually not desired after split.
		//		QScopedPointer<Mlt::Filter> filter(getFilter("fadeOutVolume", &producer));
		//		if (filter && filter->is_valid())
		//			producer.detach(*filter);
		//		filter.reset(getFilter("fadeOutBrightness", &producer));
		//		if (filter && filter->is_valid())
		//			producer.detach(*filter);
		//		filter.reset(getFilter("fadeOutMovit", &producer));
		//		if (filter && filter->is_valid())
		//			producer.detach(*filter);
		//		filter.reset(getFilter("fadeInVolume", &clip->parent()));
		//		if (filter && filter->is_valid())
		//			clip->parent().detach(*filter);
		//		filter.reset(getFilter("fadeInBrightness", &clip->parent()));
		//		if (filter && filter->is_valid())
		//			clip->parent().detach(*filter);
		//		filter.reset(getFilter("fadeInMovit", &clip->parent()));
		//		if (filter && filter->is_valid())
		//			clip->parent().detach(*filter);

		//		beginInsertRows(index(trackIndex), clipIndex, clipIndex);
		//		if (clip->is_blank()) {
		//			playlist.insert_blank(clipIndex, duration - 1);
		//		}
		//		else {
		//			playlist.insert(producer, clipIndex, in, in + duration - 1);
		//			QModelIndex modelIndex = createIndex(clipIndex, 0, trackIndex);
		//			AudioLevelsTask::start(producer.parent(), this, modelIndex);
		//		}
		//		endInsertRows();

		//		playlist.resize_clip(clipIndex + 1, in + duration, out);
		//		QModelIndex modelIndex = createIndex(clipIndex + 1, 0, trackIndex);
		//		QVector<int> roles;
		//		roles << DurationRole;
		//		roles << OutPointRole;
		//		roles << FadeInRole;
		//		emit dataChanged(modelIndex, modelIndex, roles);
		//		AudioLevelsTask::start(clip->parent(), this, modelIndex);
		//	}
		//	else {
		//		// Remove fades that are usually not desired after split.
		//		QScopedPointer<Mlt::Filter> filter(getFilter("fadeOutVolume", &clip->parent()));
		//		if (filter && filter->is_valid())
		//			clip->parent().detach(*filter);
		//		filter.reset(getFilter("fadeOutBrightness", &clip->parent()));
		//		if (filter && filter->is_valid())
		//			clip->parent().detach(*filter);
		//		filter.reset(getFilter("fadeOutMovit", &clip->parent()));
		//		if (filter && filter->is_valid())
		//			clip->parent().detach(*filter);
		//		filter.reset(getFilter("fadeInVolume", &producer));
		//		if (filter && filter->is_valid())
		//			producer.detach(*filter);
		//		filter.reset(getFilter("fadeInBrightness", &producer));
		//		if (filter && filter->is_valid())
		//			producer.detach(*filter);
		//		filter.reset(getFilter("fadeInMovit", &producer));
		//		if (filter && filter->is_valid())
		//			producer.detach(*filter);

		//		playlist.resize_clip(clipIndex, in, in + duration - 1);
		//		QModelIndex modelIndex = createIndex(clipIndex, 0, trackIndex);
		//		QVector<int> roles;
		//		roles << DurationRole;
		//		roles << OutPointRole;
		//		roles << FadeOutRole;
		//		emit dataChanged(modelIndex, modelIndex, roles);
		//		AudioLevelsTask::start(clip->parent(), this, modelIndex);

		//		beginInsertRows(index(trackIndex), clipIndex + 1, clipIndex + 1);
		//		if (clip->is_blank()) {
		//			playlist.insert_blank(clipIndex + 1, out - in - duration);
		//		}
		//		else {
		//			playlist.insert(producer, clipIndex + 1, in + duration, out);
		//			QModelIndex modelIndex = createIndex(clipIndex + 1, 0, trackIndex);
		//			AudioLevelsTask::start(producer.parent(), this, modelIndex);
		//		}
		//		endInsertRows();
		//	}

		//	emit modified();
		//}
	}

	void TimelineTracksModel::joinClips(int trackIndex, int clipIndex) {
		//if (clipIndex < 0) return;
		//int i = m_trackList.at(trackIndex).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	if (clipIndex >= playlist.count() - 1) return;
		//	QScopedPointer<Mlt::ClipInfo> info(playlist.clip_info(clipIndex));
		//	int in = info->frame_in;
		//	int duration = info->frame_count + playlist.clip_length(clipIndex + 1);

		//	// Move a fade out on the right clip onto the left clip.
		//	QScopedPointer<Mlt::Producer> clip(playlist.get_clip(clipIndex));
		//	info.reset(playlist.clip_info(clipIndex + 1));
		//	QScopedPointer<Mlt::Filter> filter(getFilter("fadeOutVolume", info->producer));
		//	if (filter && filter->is_valid())
		//		clip->parent().attach(*filter);
		//	filter.reset(getFilter("fadeOutBrightness", info->producer));
		//	if (filter && filter->is_valid())
		//		clip->parent().attach(*filter);
		//	filter.reset(getFilter("fadeOutMovit", info->producer));
		//	if (filter && filter->is_valid())
		//		clip->parent().attach(*filter);

		//	playlist.resize_clip(clipIndex, in, in + duration - 1);
		//	QModelIndex modelIndex = createIndex(clipIndex, 0, trackIndex);
		//	QVector<int> roles;
		//	roles << DurationRole;
		//	roles << OutPointRole;
		//	roles << FadeOutRole;
		//	emit dataChanged(modelIndex, modelIndex, roles);
		//	AudioLevelsTask::start(clip->parent(), this, modelIndex);

		//	beginRemoveRows(index(trackIndex), clipIndex + 1, clipIndex + 1);
		//	playlist.remove(clipIndex + 1);
		//	endRemoveRows();

		//	emit modified();
		//}
	}

	void TimelineTracksModel::fadeIn(int trackIndex, int clipIndex, int duration) {
		//int i = m_trackList.at(trackIndex).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	QScopedPointer<Mlt::ClipInfo> info(playlist.clip_info(clipIndex));
		//	if (info && info->producer && info->producer->is_valid()) {
		//		QScopedPointer<Mlt::Filter> filter;
		//		duration = qBound(0, duration, info->frame_count);

		//		if (m_trackList[trackIndex].type == VideoTrackType) {
		//			// Get video filter.
		//			if (Settings.playerGPU())
		//				filter.reset(getFilter("fadeInMovit", info->producer));
		//			else
		//				filter.reset(getFilter("fadeInBrightness", info->producer));

		//			// Add video filter if needed.
		//			if (!filter) {
		//				if (Settings.playerGPU()) {
		//					Mlt::Filter f(MLT.profile(), "movit.opacity");
		//					f.set(kShotcutFilterProperty, "fadeInMovit");
		//					QString opacity = QString("0~=0; %1=1").arg(duration - 1);
		//					f.set("opacity", opacity.toLatin1().constData());
		//					f.set("alpha", 1);
		//					info->producer->attach(f);
		//					filter.reset(new Mlt::Filter(f));
		//				}
		//				else {
		//					Mlt::Filter f(MLT.profile(), "brightness");
		//					f.set(kShotcutFilterProperty, "fadeInBrightness");
		//					QString level = QString("0=0; %1=1").arg(duration - 1);
		//					f.set("level", level.toLatin1().constData());
		//					f.set("alpha", 1);
		//					info->producer->attach(f);
		//					filter.reset(new Mlt::Filter(f));
		//				}
		//			}
		//			else if (Settings.playerGPU()) {
		//				// Special handling for animation keyframes on movit.opacity.
		//				QString opacity = QString("0~=0; %1=1").arg(duration - 1);
		//				filter->set("opacity", opacity.toLatin1().constData());
		//			}
		//			else {
		//				// Special handling for animation keyframes on brightness.
		//				QString level = QString("0=0; %1=1").arg(duration - 1);
		//				filter->set("level", level.toLatin1().constData());
		//			}
		//			// Adjust video filter.
		//			filter->set_in_and_out(info->frame_in, info->frame_in + duration - 1);
		//		}

		//		// Get audio filter.
		//		filter.reset(getFilter("fadeInVolume", info->producer));

		//		// Add audio filter if needed.
		//		if (!filter) {
		//			Mlt::Filter f(MLT.profile(), "volume");
		//			f.set(kShotcutFilterProperty, "fadeInVolume");
		//			f.set("gain", 0);
		//			f.set("end", 1);
		//			info->producer->attach(f);
		//			filter.reset(new Mlt::Filter(f));
		//		}
		//		// Adjust audio filter.
		//		filter->set_in_and_out(info->frame_in, info->frame_in + duration - 1);

		//		// Signal change.
		//		QModelIndex modelIndex = createIndex(clipIndex, 0, trackIndex);
		//		QVector<int> roles;
		//		roles << FadeInRole;
		//		emit dataChanged(modelIndex, modelIndex, roles);
		//		emit modified();
		//	}
		//}
	}

	void TimelineTracksModel::fadeOut(int trackIndex, int clipIndex, int duration) {
		//int i = m_trackList.at(trackIndex).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	QScopedPointer<Mlt::ClipInfo> info(playlist.clip_info(clipIndex));
		//	if (info && info->producer && info->producer->is_valid()) {
		//		QScopedPointer<Mlt::Filter> filter;
		//		duration = qBound(0, duration, info->frame_count);

		//		if (m_trackList[trackIndex].type == VideoTrackType) {
		//			// Get video filter.
		//			if (Settings.playerGPU())
		//				filter.reset(getFilter("fadeOutMovit", info->producer));
		//			else
		//				filter.reset(getFilter("fadeOutBrightness", info->producer));

		//			// Add video filter if needed.
		//			if (!filter) {
		//				if (Settings.playerGPU()) {
		//					Mlt::Filter f(MLT.profile(), "movit.opacity");
		//					f.set(kShotcutFilterProperty, "fadeOutMovit");
		//					QString opacity = QString("0~=1; %1=1").arg(duration - 1);
		//					f.set("opacity", opacity.toLatin1().constData());
		//					f.set("alpha", 1);
		//					info->producer->attach(f);
		//					filter.reset(new Mlt::Filter(f));
		//				}
		//				else {
		//					Mlt::Filter f(MLT.profile(), "brightness");
		//					f.set(kShotcutFilterProperty, "fadeOutBrightness");
		//					QString level = QString("0=1; %1=1").arg(duration - 1);
		//					f.set("level", level.toLatin1().constData());
		//					f.set("alpha", 1);
		//					info->producer->attach(f);
		//					filter.reset(new Mlt::Filter(f));
		//				}
		//			}
		//			else if (Settings.playerGPU()) {
		//				// Special handling for animation keyframes on movit.opacity.
		//				QString opacity = QString("0~=1; %1=0").arg(duration - 1);
		//				filter->set("opacity", opacity.toLatin1().constData());
		//			}
		//			else {
		//				// Special handling for animation keyframes on brightness.
		//				QString level = QString("0=1; %1=0").arg(duration - 1);
		//				filter->set("level", level.toLatin1().constData());
		//			}
		//			// Adjust video filter.
		//			filter->set_in_and_out(info->frame_out - duration + 1, info->frame_out);
		//		}

		//		// Get audio filter.
		//		filter.reset(getFilter("fadeOutVolume", info->producer));

		//		// Add audio filter if needed.
		//		if (!filter) {
		//			Mlt::Filter f(MLT.profile(), "volume");
		//			f.set(kShotcutFilterProperty, "fadeOutVolume");
		//			f.set("gain", 1);
		//			f.set("end", 0);
		//			info->producer->attach(f);
		//			filter.reset(new Mlt::Filter(f));
		//		}
		//		// Adjust audio filter.
		//		filter->set_in_and_out(info->frame_out - duration + 1, info->frame_out);

		//		// Signal change.
		//		QModelIndex modelIndex = createIndex(clipIndex, 0, trackIndex);
		//		QVector<int> roles;
		//		roles << FadeOutRole;
		//		emit dataChanged(modelIndex, modelIndex, roles);
		//		emit modified();
		//	}
		//}
	} 

	
	void TimelineTracksModel::moveClipToEnd(int trackIndex, int clipIndex, int position) {
		//int n = playlist.count();
		//int length = position - playlist.clip_start(n - 1) - playlist.clip_length(n - 1);

		//if (clipIndex > 0 && playlist.is_blank(clipIndex - 1)) {
		//	// If there was a blank on the left adjust it.
		//	int duration = playlist.clip_length(clipIndex - 1) + playlist.clip_length(clipIndex);
		//	//        LOG_DEBUG() << "adjust blank on left to" << duration;
		//	playlist.resize_clip(clipIndex - 1, 0, duration - 1);

		//	QModelIndex index = createIndex(clipIndex - 1, 0, trackIndex);
		//	QVector<int> roles;
		//	roles << DurationRole;
		//	emit dataChanged(index, index, roles);
		//}
		//else if ((clipIndex + 1) < n && playlist.is_blank(clipIndex + 1)) {
		//	// If there was a blank on the right adjust it.
		//	int duration = playlist.clip_length(clipIndex + 1) + playlist.clip_length(clipIndex);
		//	//        LOG_DEBUG() << "adjust blank on right to" << duration;
		//	playlist.resize_clip(clipIndex + 1, 0, duration - 1);

		//	QModelIndex index = createIndex(clipIndex + 1, 0, trackIndex);
		//	QVector<int> roles;
		//	roles << DurationRole;
		//	emit dataChanged(index, index, roles);
		//}
		//else {
		//	// Add new blank
		//	beginInsertRows(index(trackIndex), clipIndex, clipIndex);
		//	playlist.insert_blank(clipIndex, playlist.clip_length(clipIndex) - 1);
		//	endInsertRows();
		//	++clipIndex;
		//	++n;
		//}
		//// Add blank to end if needed.
		//if (length > 0) {
		//	beginInsertRows(index(trackIndex), n, n);
		//	playlist.blank(length - 1);
		//	endInsertRows();
		//}
		//// Finally, move clip into place.
		//QModelIndex parentIndex = index(trackIndex);
		//beginMoveRows(parentIndex, clipIndex, clipIndex, parentIndex, playlist.count());
		//playlist.move(clipIndex, playlist.count());
		//endMoveRows();
		//consolidateBlanks(playlist, trackIndex);
	}

	void TimelineTracksModel::relocateClip(int trackIndex, int clipIndex, int position) {
		//int targetIndex = playlist.get_clip_index_at(position);

		//if (position > playlist.clip_start(targetIndex)) {
		//	//        LOG_DEBUG() << "splitting clip at position" << position;
		//	// Split target blank clip.
		//	beginInsertRows(index(trackIndex), targetIndex, targetIndex);
		//	playlist.split_at(position);
		//	endInsertRows();
		//	if (clipIndex >= targetIndex)
		//		++clipIndex;

		//	// Notify blank on left was adjusted.
		//	QModelIndex modelIndex = createIndex(targetIndex, 0, trackIndex);
		//	QVector<int> roles;
		//	roles << DurationRole;
		//	emit dataChanged(modelIndex, modelIndex, roles);
		//	++targetIndex;
		//}

		//// Adjust blank on right.
		//int duration = playlist.clip_length(targetIndex) - playlist.clip_length(clipIndex);
		//if (duration > 0) {
		//	//        LOG_DEBUG() << "adjust blank on right" << targetIndex << " to" << duration;
		//	playlist.resize_clip(targetIndex, 0, duration - 1);
		//	// Notify blank on right was adjusted.
		//	QModelIndex modelIndex = createIndex(targetIndex, 0, trackIndex);
		//	QVector<int> roles;
		//	roles << DurationRole;
		//	emit dataChanged(modelIndex, modelIndex, roles);
		//}
		//else {
		//	//        LOG_DEBUG() << "remove blank on right";
		//	beginRemoveRows(index(trackIndex), targetIndex, targetIndex);
		//	playlist.remove(targetIndex);
		//	endRemoveRows();
		//	if (clipIndex >= targetIndex)
		//		--clipIndex;
		//}

		//// Insert clip.
		//QScopedPointer<Mlt::Producer> clip(playlist.get_clip(clipIndex));
		//QModelIndex parentIndex = index(trackIndex);
		//beginInsertRows(parentIndex, targetIndex, targetIndex);
		//playlist.insert(*clip, targetIndex, clip->get_in(), clip->get_out());
		//endInsertRows();
		//AudioLevelsTask::start(clip->parent(), this, createIndex(targetIndex, 0, trackIndex));
		//if (clipIndex >= targetIndex)
		//	++clipIndex;

		//// Replace clip with blank.
		//beginRemoveRows(parentIndex, clipIndex, clipIndex);
		//endRemoveRows();
		//beginInsertRows(parentIndex, clipIndex, clipIndex);
		//playlist.replace_with_blank(clipIndex);
		//endInsertRows();

		//consolidateBlanks(playlist, trackIndex);
	}

	void TimelineTracksModel::moveClipInBlank(int trackIndex, int clipIndex, int position) {
		//int delta = position - playlist.clip_start(clipIndex);

		//if (clipIndex > 0 && playlist.is_blank(clipIndex - 1)) {
		//	// Adjust blank on left.
		//	int duration = playlist.clip_length(clipIndex - 1) + delta;
		//	if (duration > 0) {
		//		//            LOG_DEBUG() << "adjust blank on left" << (clipIndex - 1) << "to" << duration;
		//		playlist.resize_clip(clipIndex - 1, 0, duration - 1);

		//		QModelIndex index = createIndex(clipIndex - 1, 0, trackIndex);
		//		QVector<int> roles;
		//		roles << DurationRole;
		//		emit dataChanged(index, index, roles);
		//	}
		//	else {
		//		//            LOG_DEBUG() << "remove blank on left";
		//		int i = clipIndex - 1;
		//		beginRemoveRows(index(trackIndex), i, i);
		//		playlist.remove(i);
		//		endRemoveRows();
		//		consolidateBlanks(playlist, trackIndex);
		//		--clipIndex;
		//	}
		//}
		//else if (delta > 0) {
		//	//        LOG_DEBUG() << "add blank on left with duration" << delta;
		//	// Add blank to left.
		//	int i = qMax(clipIndex, 0);
		//	beginInsertRows(index(trackIndex), i, i);
		//	playlist.insert_blank(i, delta - 1);
		//	endInsertRows();
		//	++clipIndex;
		//}

		//if ((clipIndex + 1) < playlist.count() && playlist.is_blank(clipIndex + 1)) {
		//	// Adjust blank to right.
		//	int duration = playlist.clip_length(clipIndex + 1) - delta;
		//	if (duration > 0) {
		//		//            LOG_DEBUG() << "adjust blank on right" << (clipIndex + 1) << "to" << duration;
		//		playlist.resize_clip(clipIndex + 1, 0, duration - 1);

		//		QModelIndex index = createIndex(clipIndex + 1, 0, trackIndex);
		//		QVector<int> roles;
		//		roles << DurationRole;
		//		emit dataChanged(index, index, roles);
		//	}
		//	else {
		//		//            LOG_DEBUG() << "remove blank on right";
		//		int i = clipIndex + 1;
		//		beginRemoveRows(index(trackIndex), i, i);
		//		playlist.remove(i);
		//		endRemoveRows();
		//		consolidateBlanks(playlist, trackIndex);
		//	}
		//}
		//else if (delta < 0 && (clipIndex + 1) < playlist.count()) {
		//	// Add blank to right.
		//	//        LOG_DEBUG() << "add blank on right with duration" << -delta;
		//	beginInsertRows(index(trackIndex), clipIndex + 1, clipIndex + 1);
		//	playlist.insert_blank(clipIndex + 1, (-delta - 1));
		//	endInsertRows();
		//}
	}

	void TimelineTracksModel::consolidateBlanks(int trackIndex) {
		/*for (int i = 1; i < playlist.count(); i++) {
			if (playlist.is_blank(i - 1) && playlist.is_blank(i)) {
				int out = playlist.clip_length(i - 1) + playlist.clip_length(i) - 1;
				playlist.resize_clip(i - 1, 0, out);
				QModelIndex idx = createIndex(i - 1, 0, trackIndex);
				QVector<int> roles;
				roles << DurationRole;
				emit dataChanged(idx, idx, roles);
				beginRemoveRows(index(trackIndex), i, i);
				playlist.remove(i--);
				endRemoveRows();
			}
			if (playlist.count() > 0) {
				int i = playlist.count() - 1;
				if (playlist.is_blank(i)) {
					beginRemoveRows(index(trackIndex), i, i);
					playlist.remove(i);
					endRemoveRows();
				}
			}
		}
		if (playlist.count() == 0) {
			beginInsertRows(index(trackIndex), 0, 0);
			playlist.blank(0);
			endInsertRows();
		}*/
	}

	void TimelineTracksModel::consolidateBlanksAllTracks() {
		/*if (!m_tractor) return;
		int i = 0;
		foreach(Track t, m_trackList) {
			Mlt::Producer* track = m_tractor->track(t.mlt_index);
			if (track) {
				Mlt::Playlist playlist(*track);
				consolidateBlanks(playlist, i);
			}
			++i;
		}*/
	}

	void TimelineTracksModel::audioLevelsReady(const QModelIndex& index) {
		QVector<int> roles;
		roles << AudioLevelsRole;
		emit dataChanged(index, index, roles);
	}

	bool TimelineTracksModel::createIfNeeded() {
		/*if (!m_tractor) {
			m_tractor = new Mlt::Tractor(MLT.profile());
			MLT.profile().set_explicit(true);
			m_tractor->set("shotcut", 1);
			retainPlaylist();
			addBackgroundTrack();
			addVideoTrack();
			emit created();
		}
		else if (!m_trackList.count()) {
			addVideoTrack();
		}
		return true;*/
	} 

	void TimelineTracksModel::adjustBackgroundDuration() {
	/*	if (!m_tractor) return;
		int n = 0;
		foreach(Track t, m_trackList) {
			Mlt::Producer* track = m_tractor->track(t.mlt_index);
			if (track)
				n = qMax(n, track->get_length());
			delete track;
		}
		Mlt::Producer* track = m_tractor->track(0);
		if (track) {
			Mlt::Playlist playlist(*track);
			Mlt::Producer* clip = playlist.get_clip(0);
			if (clip) {
				if (n != clip->parent().get_length()) {
					clip->parent().set("length", n);
					clip->parent().set_in_and_out(0, n - 1);
					clip->set("length", n);
					clip->set_in_and_out(0, n - 1);
					playlist.resize_clip(0, 0, n - 1);
					emit durationChanged();
				}
				delete clip;
			}
			delete track;
		}*/
	} 

	void TimelineTracksModel::removeRegion(int trackIndex, int position, int length) {
		//int i = m_trackList.at(trackIndex).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	int clipIndex = playlist.get_clip_index_at(position);

		//	if (clipIndex >= 0 && clipIndex < playlist.count())
		//	{
		//		int clipStart = playlist.clip_start(clipIndex);
		//		int playtime = playlist.get_playtime();
		//		playlist.block(playlist.get_playlist());

		//		if (position + length > playtime)
		//			length -= (position + length - playtime);

		//		if (clipStart < position) {
		//			splitClip(trackIndex, clipIndex, position);
		//			++clipIndex;
		//		}

		//		while (length > 0) {
		//			if (playlist.clip_length(clipIndex) > length) {
		//				splitClip(trackIndex, clipIndex, position + length);
		//			}
		//			length -= playlist.clip_length(clipIndex);
		//			if (clipIndex < playlist.count()) {
		//				// Shotcut does not like the behavior of remove() on a
		//				// transition (MLT mix clip). So, we null mlt_mix to prevent it.
		//				QScopedPointer<Mlt::Producer> producer(playlist.get_clip(clipIndex));
		//				if (producer)
		//					producer->parent().set("mlt_mix", NULL, 0);
		//				beginRemoveRows(index(trackIndex), clipIndex, clipIndex);
		//				playlist.remove(clipIndex);
		//				endRemoveRows();
		//			}
		//		}
		//		playlist.unblock(playlist.get_playlist());
		//		consolidateBlanks(playlist, trackIndex);
		//	}
		//}
	}  

	void TimelineTracksModel::insertOrAdjustBlankAt(QList<int> tracks, int position, int length) {
		/*foreach(int trackIndex, tracks) {
			int mltIndex = m_trackList.at(trackIndex).mlt_index;
			QScopedPointer<Mlt::Producer> otherTrack(m_tractor->track(mltIndex));

			if (otherTrack) {
				Mlt::Playlist trackPlaylist(*otherTrack);
				int idx = trackPlaylist.get_clip_index_at(position);

				if (trackPlaylist.is_blank(idx)) {
					trackPlaylist.resize_clip(idx, 0, trackPlaylist.clip_length(idx) + length - 1);
					QModelIndex modelIndex = createIndex(idx, 0, trackIndex);
					emit dataChanged(modelIndex, modelIndex, QVector<int>() << DurationRole);
				}
				else if (length > 0) {
					int insertBlankAtIdx = idx;
					if (trackPlaylist.clip_start(idx) < position) {
						splitClip(trackIndex, idx, position);
						insertBlankAtIdx = idx + 1;
					}
					beginInsertRows(index(trackIndex), insertBlankAtIdx, insertBlankAtIdx);
					trackPlaylist.insert_blank(insertBlankAtIdx, length - 1);
					endInsertRows();
				}
				else {
					Q_ASSERT(!"unsupported");
				}
			}
		}*/
	}

	bool TimelineTracksModel::mergeClipWithNext(int trackIndex, int clipIndex, bool dryrun) {
	/*	int i = m_trackList.at(trackIndex).mlt_index;
		QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		if (!track)
			return false;
		Mlt::Playlist playlist(*track);
		if (clipIndex >= playlist.count() + 1)
			return false;
		Mlt::ClipInfo clip1;
		Mlt::ClipInfo clip2;
		playlist.clip_info(clipIndex, &clip1);
		playlist.clip_info(clipIndex + 1, &clip2);

		if (QString::fromUtf8(clip1.resource) != QString::fromUtf8(clip2.resource))
			return false;

		if (clip1.frame_out + 1 != clip2.frame_in)
			return false;

		if (dryrun)
			return true;

		playlist.resize_clip(clipIndex, clip1.frame_in, clip1.frame_out + clip2.frame_count);
		QModelIndex modelIndex = createIndex(clipIndex, trackIndex);
		QVector<int> roles;
		roles << DurationRole;
		roles << InPointRole;
		emit dataChanged(modelIndex, modelIndex, roles);

		beginRemoveRows(index(trackIndex), clipIndex + 1, clipIndex + 1);
		playlist.remove(clipIndex + 1);
		endRemoveRows();
		emit modified();
		return true;*/
	}
	 

	void TimelineTracksModel::load() {
		//if (m_tractor) {
		//	beginResetModel();
		//	delete m_tractor;
		//	m_tractor = 0;
		//	m_trackList.clear();
		//	endResetModel();
		//}
		//// In some versions of MLT, the resource property is the XML filename,
		//// but the Mlt::Tractor(Service&) constructor will fail unless it detects
		//// the type as tractor, and mlt_service_identify() needs the resource
		//// property to say "<tractor>" to identify it as playlist type.
		//MLT.producer()->set("mlt_type", "mlt_producer");
		//MLT.producer()->set("resource", "<tractor>");
		//MLT.profile().set_explicit(true);
		//m_tractor = new Mlt::Tractor(*MLT.producer());
		//if (!m_tractor->is_valid()) {
		//	delete m_tractor;
		//	m_tractor = 0;
		//	return;
		//}

		//loadPlaylist();
		//addBlackTrackIfNeeded();
		//MLT.updateAvformatCaching(m_tractor->count());
		//refreshTrackList();
		//convertOldDoc();
		//consolidateBlanksAllTracks();
		//adjustBackgroundDuration();
		//if (m_trackList.count() > 0) {
		//	beginInsertRows(QModelIndex(), 0, m_trackList.count() - 1);
		//	endInsertRows();
		//	getAudioLevels();
		//}
		//emit loaded();
		//emit filteredChanged();
	}

	void TimelineTracksModel::reload() {
	/*	if (m_tractor) {
			beginResetModel();
			endResetModel();
			getAudioLevels();
			emit filteredChanged();
		}*/
	}

	void TimelineTracksModel::close() {
		/*if (!m_tractor) return;
		if (m_trackList.count() > 0) {
			beginRemoveRows(QModelIndex(), 0, m_trackList.count() - 1);
			m_trackList.clear();
			endRemoveRows();
		}
		delete m_tractor;
		m_tractor = 0;
		emit closed();*/
	}

	int TimelineTracksModel::clipIndex(int trackIndex, int position) {
		//int i = m_trackList.at(trackIndex).mlt_index;
		//QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
		//if (track) {
		//	Mlt::Playlist playlist(*track);
		//	return playlist.get_clip_index_at(position);
		//}
		//return -1; // error
	}

	void TimelineTracksModel::getAudioLevels() {
		/*	for (int trackIx = 0; trackIx < m_trackList.size(); trackIx++) {
				int i = m_trackList.at(trackIx).mlt_index;
				QScopedPointer<Mlt::Producer> track(m_tractor->track(i));
				Mlt::Playlist playlist(*track);
				for (int clipIx = 0; clipIx < playlist.count(); clipIx++) {
					QScopedPointer<Mlt::Producer> clip(playlist.get_clip(clipIx));
					if (clip && clip->is_valid() && !clip->is_blank() && clip->get_int("audio_index") > -1) {
						QModelIndex index = createIndex(clipIx, 0, trackIx);
						AudioLevelsTask::start(clip->parent(), this, index);
					}
				}
			}*/
	}

	void TimelineTracksModel::removeBlankPlaceholder(int trackIndex) {
		/*if (playlist.count() == 1 && playlist.is_blank(0)) {
			beginRemoveRows(index(trackIndex), 0, 0);
			playlist.remove(0);
			endRemoveRows();
		}*/
	}

}


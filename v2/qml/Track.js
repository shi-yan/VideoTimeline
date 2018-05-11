var SNAP = 10

function snapClip(clip, repeater) {
    var left = clip.x
    var right = clip.x + clip.width
    if (clip.x > -SNAP && clip.x < SNAP) {
        // Snap around origin.
        clip.x = 0
        return
    } else {
        // Snap to other clips.
        for (var i = 0; i < repeater.count; i++) {
            // Do not snap to self.
            if (i === clip.DelegateModel.itemsIndex && clip.trackIndex === repeater.itemAt(i).trackIndex)
                continue
            var itemLeft = repeater.itemAt(i).x
            var itemRight = itemLeft + repeater.itemAt(i).width
            // Snap to blank
            if (right > itemLeft - SNAP && right < itemLeft + SNAP) {
                // Snap right edge to left edge.
                clip.x = itemLeft - clip.width
                return
            } else if (left > itemRight - SNAP && left < itemRight + SNAP) {
                // Snap left edge to right edge.
                clip.x = itemRight
                return
            } else if (right > itemRight - SNAP && right < itemRight + SNAP) {
                // Snap right edge to right edge.
                clip.x = itemRight - clip.width
                return
            } else if (left > itemLeft - SNAP && left < itemLeft + SNAP) {
                // Snap left edge to left edge.
                clip.x = itemLeft
                return
            }
        }
    }

    var cursorX = scrollView.flickableItem.contentX + cursor.x
    if (left > cursorX - SNAP && left < cursorX + SNAP)
        // Snap around cursor/playhead.
        clip.x = cursorX
    if (right > cursorX - SNAP && right < cursorX + SNAP)
        clip.x = cursorX - clip.width 
}

function snapTrimIn(clip, delta) {
    var x = clip.x + delta
    var cursorX = scrollView.flickableItem.contentX + cursor.x
    if (false) {
        // Snap to other clips.
        for (var i = 0; i < repeater.count; i++) {
            if (i === clip.DelegateModel.itemsIndex || repeater.itemAt(i).isBlank)
                continue
            var itemLeft = repeater.itemAt(i).x
            var itemRight = itemLeft + repeater.itemAt(i).width
            if (x > itemLeft - SNAP && x < itemLeft + SNAP)
                return Math.round((itemLeft - clip.x) / timeScale)
            else if (x > itemRight - SNAP && x < itemRight + SNAP)
                return Math.round((itemRight - clip.x) / timeScale)
        }
    }
    if (x > -SNAP && x < SNAP) {
        // Snap around origin.
        return Math.round(-clip.x / timeScale)
    } else if (x > cursorX - SNAP && x < cursorX + SNAP) {
        // Snap around cursor/playhead.
        return Math.round((cursorX - clip.x) / timeScale)
    }
    return delta
}

function snapTrimOut(clip, delta) {
    var rightEdge = clip.x + clip.width
    var x = rightEdge - delta
    var cursorX = scrollView.flickableItem.contentX + cursor.x
    if (delta < 0) {
        // Snap to other clips.
        for (var i = 0; i < repeater.count; i++) {
            if (i === clip.DelegateModel.itemsIndex || repeater.itemAt(i).isBlank || repeater.itemAt(i).isTransition)
                continue
            var itemLeft = repeater.itemAt(i).x
            var itemRight = itemLeft + repeater.itemAt(i).width
            if (x > itemLeft - SNAP && x < itemLeft + SNAP)
                return Math.round((rightEdge - itemLeft) / timeScale)
            else if (x > itemRight - SNAP && x < itemRight + SNAP)
                return Math.round((rightEdge - itemRight) / timeScale)
        }
    }
    if (x > cursorX - SNAP && x < cursorX + SNAP) {
        // Snap around cursor/playhead.
        return Math.round((rightEdge - cursorX) / timeScale)
    }
    return delta
}

function snapDrop(pos, repeater) {
    var left = scrollView.flickableItem.contentX + pos.x - headerWidth
    var right = left + dropTarget.width
    if (left > -SNAP && left < SNAP) {
        // Snap around origin.
        dropTarget.x = headerWidth
        return
    } else {
        // Snap to other clips.
        for (var i = 0; i < repeater.count; i++) {
            var itemLeft = repeater.itemAt(i).x
            var itemRight = itemLeft + repeater.itemAt(i).width
            if (right > itemLeft - SNAP && right < itemLeft + SNAP) {
                dropTarget.x = itemLeft - dropTarget.width + headerWidth - scrollView.flickableItem.contentX
                return
            } else if (left > itemRight - SNAP && left < itemRight + SNAP) {
                dropTarget.x = itemRight + headerWidth - scrollView.flickableItem.contentX
                return
            }
        }
    } 
    var cursorX = scrollView.flickableItem.contentX + cursor.x
    if (left > cursorX - SNAP && left < cursorX + SNAP)
        // Snap around cursor/playhead.
        dropTarget.x = cursorX + headerWidth - scrollView.flickableItem.contentX
    if (right > cursorX - SNAP && right < cursorX + SNAP)
        dropTarget.x = cursorX - dropTarget.width + headerWidth - scrollView.flickableItem.contentX 
}

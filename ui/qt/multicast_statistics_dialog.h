/** @file
 *
 * Wireshark - Network traffic analyzer
 * By Gerald Combs <gerald@wireshark.org>
 * Copyright 1998 Gerald Combs
 *
 * SPDX-License-Identifier: GPL-2.0-or-later
 */

#ifndef MULTICASTSTATISTICSDIALOG_H
#define MULTICASTSTATISTICSDIALOG_H

#include "tap_parameter_dialog.h"
#include "ui/mcast_stream.h"

class SyntaxLineEdit;

class MulticastStatisticsDialog : public TapParameterDialog
{
    Q_OBJECT

public:
    MulticastStatisticsDialog(QWidget &parent, CaptureFile &cf, const char *filter = NULL);
    ~MulticastStatisticsDialog();

protected:
    void captureFileClosing();

private:
    struct _mcaststream_tapinfo *tapinfo_;
    SyntaxLineEdit *burst_measurement_interval_le_;
    SyntaxLineEdit *burst_alarm_threshold_le_;
    SyntaxLineEdit *buffer_alarm_threshold_le_;
    SyntaxLineEdit *stream_empty_speed_le_;
    SyntaxLineEdit *total_empty_speed_le_;
    QList<QWidget *> line_edits_;

    // Callbacks for register_tap_listener
    static void tapReset(mcaststream_tapinfo_t *tapinfo);
    static void tapDraw(mcaststream_tapinfo_t *tapinfo);

    void rescan();

    virtual QList<QVariant> treeItemData(QTreeWidgetItem *ti) const;
    virtual const QString filterExpression();

private slots:
    void updateWidgets();
    void updateMulticastParameters();
    virtual void fillTree();
};

#endif // MULTICASTSTATISTICSDIALOG_H

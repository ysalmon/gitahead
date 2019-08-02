//
//          Copyright (c) 2016, Scientific Toolworks, Inc.
//
// This software is licensed under the MIT License. The LICENSE.md file
// describes the conditions under which this software may be distributed.
//
// Author: Jason Haslam
//

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "git/Repository.h"
#include <QMainWindow>

class RepoView;
class TabWidget;
class ToolBar;

namespace git {
class Submodule;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(const git::Repository& repo, QWidget* parent = nullptr, Qt::WindowFlags flags = 0, bool doNotStartView = false);
  MainWindow(const git::Repository& repo, bool doNotStartView) : MainWindow(repo, nullptr, 0, doNotStartView) {};

  ToolBar *toolBar() const { return mToolBar; }

  bool isSideBarVisible() const;
  void setSideBarVisible(bool visible);

  TabWidget *tabWidget() const;
  RepoView *addTab(const QString &path, bool doNotStartView = false);
  RepoView *addTab(const git::Repository &repo, bool doNotStartView = false);

  int count() const;
  RepoView *currentView() const;
  RepoView *view(int index) const;

  // Get the "active" main window.
  static MainWindow *activeWindow();
  static QList<MainWindow *> windows();

  // Restore previous open window state.
  // Returns true if any windows were opened.
  static bool restoreWindows();

  // Open a new window.
  static MainWindow *open(const QString &path, bool warnOnInvalid = true, bool doNotStartView = false);
  static MainWindow *open(const git::Repository &repo = git::Repository(), bool doNotStartView = false);

  // Avoid updating interface during exit.
  static void setExiting(bool exiting);

  // Save window settings on close.
  static void setSaveWindowSettings(bool enabled);

protected:
  void showEvent(QShowEvent *event) override;
  void closeEvent(QCloseEvent *event) override;
  void dragEnterEvent(QDragEnterEvent *event) override;
  void dropEvent(QDropEvent *event) override;

private:
  void updateInterface();
  void updateWindowTitle(int ahead = -1, int behind = -1);

  static void warnInvalidRepo(const QString &path);

  QStringList paths() const;
  QString windowGroup() const;

  void installTouchBar();
  void updateTouchBar(int ahead = -1, int behind = -1);

  ToolBar *mToolBar;
  bool mFullPath = false;
  bool mIsSideBarVisible = true;

  bool mShown = false;

  static bool sDoNotStartViews;
  static bool sExiting;
  static bool sSaveWindowSettings;
};

#endif

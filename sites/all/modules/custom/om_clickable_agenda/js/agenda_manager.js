(function ($, Drupal, window, document, undefined) {
  Drupal.behaviors.agendaManager = {
    attach : function(context) {
      // Instantiate a new instance of our app.
      $target = $('#content', context);
      if ($target && !$target.hasClass('agenda-manager-processed') && Drupal.settings.clickableAgenda.currentNodeId && Drupal.settings.clickableAgenda.themeNid && JSON) {
        $target.addClass('agenda-manager-processed');
        $target.addClass('clearfix');
        var app = new Drupal.agendaManger.Views.appView($target, Drupal.settings.clickableAgenda.currentNodeId, Drupal.settings.clickableAgenda.themeNid, Drupal.settings.clickableAgenda.sessionStatus);
      }
    }
  };

// Define wrappers to store a few classes.
Drupal.agendaManger = Drupal.agendaManger || {};
Drupal.agendaManger.Views = Drupal.agendaManger.Views || {};
Drupal.agendaManger.Models = Drupal.agendaManger.Models || {};
Drupal.agendaManger.Collections = Drupal.agendaManger.Collections || {}; 

/**
 * MODELS:
 *   Interpreter model -- paired with app view as its storage mechanism.
 */
Drupal.agendaManger.Models.interpreter = Backbone.Model.extend({
  initialize : function() {
    _.bindAll(this, 'retrieveData', 'addSessionBills', 'addCuePoints', 'dataComplete', 'toggleTimer', 'startTimer', 'stopTimer', 'resetTimer', 'initializeTimer', 'calcTime', 'newCuePointHelper', 'updateCuePointListView', 'saveSessionStatus');
    // Create and stash a preloader
    this.preloader = new Drupal.agendaManger.Views.preloader();
    $(this.get('parent').el).append(this.preloader.domElement);
    this.preloader.hide();
    // Bill List
    this.billListView = new Drupal.agendaManger.Views.billListView();
    this.billList = new Drupal.agendaManger.Collections.sessionBillList();
    this.billListView.on('billListView:click', this.newCuePointHelper, this);
    this.billList.on('add', this.billListView.addDomElement, this.billListView);
    $(this.get('parent').el).append(this.billListView.domElement);
    // Cue Point List
    this.cuePointListView = new Drupal.agendaManger.Views.cuePointList();
    this.cuePointList = new Drupal.agendaManger.Collections.cuePointList();
    this.cuePointList.on('cuePointList:cuePointListChange', this.updateCuePointListView, this);
    $(this.get('parent').el).append(this.cuePointListView.domElement);
    // Session controller
    this.sessionControllerView = new Drupal.agendaManger.Views.sessionController();
    this.sessionControllerView.on('sessionController:toggleTimer', this.toggleTimer, this);
    this.sessionControllerView.on('sessionController:submit', this.newCuePointHelper, this);
    this.on('timeChange', this.sessionControllerView.updateTimerWrapper, this.sessionControllerView);
    this.set('appState', 'loading');
    // Session status
    this.sessionStatusView = new Drupal.agendaManger.Views.sessionStatus();
    this.on('change', this.sessionStatusView.updateView);
    // Timer stuff
    this.set('timerState', false);
    this.set('currentTime', 0);
  },
  retrieveData : function() {
    $.ajax({
      type : 'GET',
      url : '/node/' + this.get('currentNid') + '/agenda-items',
      success : this.addSessionBills
    });
    $.ajax({
      type : 'GET',
      url : '/node/' + this.get('currentNid') + '/agenda-items?source=stamped&format=field-json',
      success : this.addCuePoints
    });
    var obj = {'nid' : this.get('currentNid')};
    var json = JSON.stringify(obj);
    $.ajax({
      type : 'POST',
      url : '/get-agenda-session',
      success : this.initializeTimer,
      data : {'sessionQuery' : json}
    });
  },
  addSessionBills : function(data) {
    //dataJSON = JSON.parse(data);
    for (x in data) {
      this.billList.add(data[x]);
    }
    this.set('sessionBillsComplete', true);
  },
  addCuePoints : function(data) {
    //dataJSON = JSON.parse(data);
    for (x in data) {
      this.cuePointList.add(data[x]);
    }
    this.updateCuePointListView();
    this.set('addCuePointsComplete', true);
  },
  dataComplete : function() {
    if (this.get('sessionBillsComplete') == true && this.get('addCuePointsComplete') == true) {
      this.set('appState', 'ready');
    }
  },
  toggleTimer : function() {
    if (this.get('timerState') == true) {
      this.set('timerState', false);
      this.stopTimer();
      if (this.sessionControllerView.sessionToggleLive && this.sessionControllerView.sessionToggleLive.attr('checked')) {
        var newValues = this.get('sessionStatus');
        var theme = this.get('themeNid');
        newValues[theme].live_nid = this.get('currentNid');
        newValues[theme].status = false;
        this.set('sessionStatus', newValues);
        this.saveSessionStatus();
      }
    }
    else {
      this.set('timerState', true);
      this.startTimer();
      if (this.sessionControllerView.sessionToggleLive && this.sessionControllerView.sessionToggleLive.attr('checked')) {
        var newValues = this.get('sessionStatus');
        var theme = this.get('themeNid');
        newValues[theme].live_nid = this.get('currentNid');
        newValues[theme].status = true;
        this.set('sessionStatus', newValues);
        this.saveSessionStatus();
      }
    }
  },
  startTimer : function() {
    if (this.sessionControllerView.timeInput) {
      var start = formatTimeTimestamp(this.sessionControllerView.timeInput.val());
      this.set('currentTime', start);
    }
    this.timerInterval = setInterval(this.calcTime, 1005);
    if (this.sessionControllerView.sessionToggleLive.attr('checked')) {
      // Also clear database record
      var obj = {'nid' : this.get('currentNid')};
      var json = JSON.stringify(obj);
      $.ajax({
        type : 'POST',
        url : '/write-agenda-session',
        data : {'customSession' : json}
      });
    }
  },
  stopTimer : function() {
    clearInterval(this.timerInterval);
    this.resetTimer();
    if (this.sessionControllerView.sessionToggleLive.attr('checked')) {
      // Also clear database record
      var obj = {'nid' : this.get('currentNid')};
      var json = JSON.stringify(obj);
      $.ajax({
        type : 'POST',
        url : '/delete-agenda-session',
        data : {'sessionQuery' : json}
      });
    }
  },
  resetTimer : function() {
    this.set('currentTime', 0);
    this.trigger('timeChange', this.get('currentTime'));
  },
  initializeTimer : function(data) {
    var obj = JSON.parse(data);
    var currentValues = this.get('sessionStatus');
    if (obj && obj.nid) {
      _.each(currentValues, function(zetheme) {
        if (zetheme.status) {
          if (obj.nid == zetheme.live_nid) {
            this.sessionControllerView.toggleTimer();
            this.sessionControllerView.sessionToggleLive.trigger('change');
            this.sessionControllerView.sessionToggleLive.attr('checked', 'checked');
          } 
        }
      }, this);
    }
    /**
    if (obj && obj.nid && ((obj.nid == currentValues.houseSession && currentValues.house == "Live") || (obj.nid == currentValues.senateSession && currentValues.senate == "Live"))) {
      this.sessionControllerView.toggleTimer();
      this.sessionControllerView.sessionToggleLive.trigger('change');
      this.sessionControllerView.sessionToggleLive.attr('checked', 'checked');
    }**/
  },
  calcTime : function() {
    var newTime = this.get('currentTime') + 1;
    this.set('currentTime', newTime);
    this.trigger('timeChange', this.get('currentTime'));
  },
  newCuePointHelper : function(data) {
    if (data['node_revisions_body']) {
      data.title = data['node_revisions_body'];
    }
    else {
      data.title = new Date().getTime();
    }
    data['node_data_field_cue_seconds_field_cue_seconds_value'] = formatTimeTimestamp(this.sessionControllerView.timeInput.val());
    data['node_data_field_session_reference_field_session_reference_nid'] = this.get('currentNid');
    this.cuePointList.add(data);
    this.cuePointListView.updateView(this.cuePointList.models);
  },
  updateCuePointListView : function() {
    this.cuePointListView.updateView(this.cuePointList.models);
  },
  saveSessionStatus : function() {
    var values = this.get('sessionStatus');
    var modelPost = {'sessionStatus' : JSON.stringify(values)};
    $.ajax({
      type : 'post',
      url : '/change-session-status',
      data : modelPost,
    });
  }
});

// Cue point model
Drupal.agendaManger.Models.cuePoint = Backbone.Model.extend({
  initialize : function() {
    _.bindAll(this, 'saveModel', 'updateModel', 'deleteModel', 'handleResponse', 'inlineEditListener');
  },
  saveModel : function() {
   var modelPost = {'node' : JSON.stringify(this.attributes)};
    $.ajax({
      url : '/create-cue-point',
      data : modelPost,
      type : 'POST',
      success : this.handleResponse
    });
  },
  handleResponse : function(data) {
    dataJSON = JSON.parse(data);
    if (!this.get('nid')) {
      this.set('nid', dataJSON.nid);
    }
  },
  updateModel : function(data) {
    this.set(data);
    this.saveModel();
    this.trigger('cuePoint:modelChange', this);
  },
  deleteModel : function() {
    this.trigger('cuePoint:deleteModel', this);
  },
  inlineEditListener : function() {
    this.trigger('cuePoint:inlineEdit', this);
  }
});

// Session bill model
Drupal.agendaManger.Models.sessionBill = Backbone.Model.extend({});

/**
 * Collections:
 *   Session Bill Collection
 */
Drupal.agendaManger.Collections.sessionBillList = Backbone.Collection.extend({
  model : Drupal.agendaManger.Models.sessionBill
});
// Cue point collection
Drupal.agendaManger.Collections.cuePointList = Backbone.Collection.extend({
  initialize : function() {
    _.bindAll(this, 'cuePointListChange');
    this.on('add', this.saveNewModel, this);
    this.on('cuePoint:modelChange', this.cuePointListChange);
  },
  comparator : function (model) {
    return -model.get('node_data_field_cue_seconds_field_cue_seconds_value');
  },
  model : Drupal.agendaManger.Models.cuePoint,
  saveNewModel : function(model) {
    model.view = new Drupal.agendaManger.Views.cuePointView();
    // This part is a bit kludgy, but I think this is cleaner than storing a model on the domElement.
    // We attach the view's inline edit event to the model's inlineEditListener.
    // The model intern triggers the view's inlineEditToggle sending a reference to itself as the parameter.
    // Basically, this listView acts as an interpeter for the cuePoint view and model.
    model.view.on('cuePointView:inlineEdit', model.inlineEditListener, model);
    model.view.on('cuePointView:submit', model.updateModel, model);
    model.on('cuePoint:inlineEdit', model.view.inlineEditToggle, model);
    // Similar for deletion
    model.view.on('cuePointView:deleteModel', model.deleteModel, model);
    model.on('cuePoint:deleteModel', this.deleteModel, this);
    if (!model.get('nid')) {
      model.saveModel();
    } 
  },
  cuePointListChange : function() {
    this.sort();
    this.trigger('cuePointList:cuePointListChange');
  },
  deleteModel : function(model) {
    if (confirm("Are you sure you want to delete the cue point: " + model.get('node_revisions_body'))) {
      var modelPost = {'node' : JSON.stringify(model.attributes)};
      model.view.domElement.remove();
      this.remove(model);
      $.ajax({
        url : '/delete-cue-point',
        data : modelPost,
        type : 'POST'
      });
    }
  }
});

/**
 * Views:
 */
Drupal.agendaManger.Views.appView = Backbone.View.extend({
  initialize : function(el, currentNid, themeNid, sessionStatus) {
    _.bindAll(this, 'updateView');
    // Store DOM Reference
    this.setElement(el);
    // Instantiate and prepare interpreter.
    this.interpreter = new Drupal.agendaManger.Models.interpreter({'parent' : this});
    this.interpreter.set('parent', this);
    this.interpreter.set('currentNid', currentNid);
    this.interpreter.set('themeNid', themeNid);
    this.interpreter.set('sessionStatus', sessionStatus);
    this.interpreter.on('change', this.updateView, this);
    this.interpreter.retrieveData();
  },
  updateView : function(model) {
    // Handle changes in larger application state.
    if (model.changed.appState) {
      if (model.get('appState') == 'loading') {
        this.interpreter.preloader.show();
      }
      else if(model.get('appState') == 'ready') {
        this.interpreter.preloader.hide();
      }
    }
  }
});

// Small preloader view
Drupal.agendaManger.Views.preloader = Backbone.View.extend({
  initialize : function() {
    _.bindAll(this, 'show', 'hide');
    this.domElement = $('<div/>').addClass('agenda-manager-preloader').text('loading...');
  },
  show : function() {
    this.domElement.show();
  },
  hide : function() {
    this.domElement.hide();
  }
});
// Bill list view
Drupal.agendaManger.Views.billListView = Backbone.View.extend({
  initialize : function() {
    _.bindAll(this, 'addDomElement', 'template', 'handleClick');
    this.domElement = $('<div/>').attr('id', 'bill-list');
  },
  addDomElement : function(model) {
    this.domElement.append(this.template(model));
  },
  template : function(model) {
    var $domElement = $('<div/>').addClass('bill-list-item');
    $addButton = $('<div/>').addClass('ca-grey-button').text('+ Add');
    $addButton.click(this.handleClick);
    $text = $('<div/>').addClass('bill-title').text(model.get('title'));
    $domElement.append($text).append($addButton);
    return $domElement;
  },
  handleClick : function(e) {
    var values = {'node_revisions_body' : $(e.target).siblings('.bill-title').text()};
    this.trigger('billListView:click', values);
  }
});
// Cuepoint List View
Drupal.agendaManger.Views.cuePointList = Backbone.View.extend({
  initialize : function() {
    _.bindAll(this, 'addDomElement', 'updateView');
    this.domElement = $('<div/>').attr('id', 'cue-point-list');
  },
  addDomElement : function(model) {
    // Prepends a single model to the list.
    this.domElement.prepend(model.view.addDomElement(model));
  },
  updateView : function(models) {
    // Updates the entire view.
    for (x in models) {
      if (!models[x].view.domElement) {
        models[x].view.addDomElement(models[x]);
      }
      this.domElement.append(models[x].view.domElement);
    }
  }
});

// Individual Cuepoint View
Drupal.agendaManger.Views.cuePointView = Backbone.View.extend({
  initialize : function() {
    _.bindAll(this, 'addDomElement', 'template', 'editClickHandler', 'saveInlineForm', 'inlineEditToggle', 'deleteModel');
  },
  addDomElement : function(model) {
    this.template(model, 'view');
    return this.domElement;
  },
  template : function(model, mode) {
    model.set('viewMode', mode);
    if (this.domElement) {
      this.domElement.find('.cue-point-edit').unbind('click');
    }
    if (mode == 'view') {
      var $domElement = $('<div/>').addClass('cue-point-list-item clearfix');
      var $title = $('<div/>').addClass('cue-point-title').text(model.get('node_revisions_body'));
      var $time = $('<div/>').addClass('cue-point-seconds').text(formatTimeHuman(model.get('node_data_field_cue_seconds_field_cue_seconds_value')));
      var $edit = $('<div/>').addClass('ca-grey-button action-edit cue-point-edit').text('edit');
      $edit.click(this.editClickHandler);
      $delete = $('<div/>').addClass('ca-grey-button action-delete cue-point-edit').text('delete');
      $delete.click(this.deleteModel);
      $domElement.append($title).append($time).append($edit).append($delete);
      this.domElement = $domElement;
      return $domElement;
    }
    else if (mode == 'edit') {
      var $domElement = $('<div/>').addClass('cue-point-list-item clearfix');
      var $title = $('<textarea/>').addClass('cue-point-title').attr({'value' : model.get('node_revisions_body')});
      var $time = $('<textarea/>').addClass('cue-point-seconds').attr({'value' : formatTimeHuman(model.get('node_data_field_cue_seconds_field_cue_seconds_value'))});
      var $edit = $('<div/>').addClass('ca-grey-button action-save cue-point-edit').text('save');
      $edit.click(this.saveInlineForm);
      $delete = $('<div/>').addClass('ca-grey-button action-delete cue-point-edit').text('delete');
      $delete.click(this.deleteModel);
      $domElement.append($title).append($time).append($edit).append($delete);
      this.domElement = $domElement;
      return $domElement;
    }
  },
  editClickHandler : function(e) {
    this.trigger('cuePointView:inlineEdit');
  },
  saveInlineForm : function(e) {
    var values = {'title' : $(this.domElement).find('.cue-point-title').val(), 'node_revisions_body' : $(this.domElement).find('.cue-point-title').val(), 'node_data_field_cue_seconds_field_cue_seconds_value' : formatTimeTimestamp($(this.domElement).find('.cue-point-seconds').val())};
    this.trigger('cuePointView:submit', values);
    this.trigger('cuePointView:inlineEdit');
  },
  inlineEditToggle : function(model) {
    if (model.get('viewMode') == 'view') {
      this.domElement.replaceWith(this.template(model, 'edit'));
    }
    else if (model.get('viewMode') == 'edit') {
      this.domElement.replaceWith(this.template(model, 'view'));
    }
  },
  deleteModel : function() {
    this.trigger('cuePointView:deleteModel');
  }
});

// Session Controller View.
Drupal.agendaManger.Views.sessionController = Backbone.View.extend({
  initialize : function() {
    _.bindAll(this, 'toggleTimer', 'updateTimerWrapper', 'sessionControllerSubmit', 'toggleSelect');
    // Add timer controls
    this.setElement($('#agenda-manager-form'));
    $(this.el).addClass('clearfix');
    // Find toggle and attach click handler
    this.button = $(this.el).find('#agenda-time-toggle');
    this.button.click(this.toggleTimer);
    // Find input and hijack
    this.timeInput = $(this.el).find('#timer-wrapper');
    // Now handle form submit
    $(this.el).submit(this.sessionControllerSubmit);
    // Stuff for changing live session status.
    this.sessionToggleLive = $(this.el).find('#edit-session-toggle-live');
    this.sessionToggleLive.change(this.toggleSelect);
    //this.sessionType = $(this.el).find('#edit-session-type');
    //this.sessionType.attr('disabled', 'disabled');
  },
  toggleTimer : function(e) {
    if (!this.button.hasClass('active')) {
      this.button.addClass('active');
      this.button.text("Reset Timer");
      this.trigger('sessionController:toggleTimer');
    }
    else if (this.button.hasClass('active')) {
      if (confirm('Are you sure you want to reset the timer for the live session.')) {
        this.button.removeClass('active');
        this.button.text("Start Timer");
        this.trigger('sessionController:toggleTimer');
      }
    }
  },
  updateTimerWrapper : function(time) {
    if (typeof(time) == 'string') {
      time = parseInt(time);
    }
    time = formatTimeHuman(time);
    this.timeInput.val(time);
  },
  sessionControllerSubmit : function(e) {
    e.preventDefault();
    var values = {'node_revisions_body' : $(this.el).find('#edit-add-bill-box').val()};
    this.trigger('sessionController:submit', values);
  },
  toggleSelect : function() {
    /**
    if (this.sessionType.attr('disabled')) {
       this.sessionType.attr('disabled', '');
    }
    else {
     this.sessionType.attr('disabled', 'disabled');
    }**/
  }
});
// Session Status View
Drupal.agendaManger.Views.sessionStatus = Backbone.View.extend({
  initialize : function() {
    _.bindAll(this, 'updateView');
    this.setElement($('#session-status'));
    this.activeSessions = $(this.el).siblings('#active-sessions');
  },
  updateView : function(model) {
    /**
    var sessionStatus = model.get('sessionStatus');
    if (sessionStatus) {
      var $ul = $('<ul/>');
      for (x in sessionStatus) {
        if (sessionStatus[x] && x == 'house' || x == 'senate') {
          var $li = $('<li/>').addClass(sessionStatus[x].toLowerCase()).text(x + ' - ' + sessionStatus[x].toLowerCase());
          $ul.append($li);
        }
      }
      $(this.el).empty().append($ul);
      
    }
    **/
  }
});

/**
 * Private helper functions
 */

/**
 * Convert arbitrary seconds to HH:MM:SS format.
 */
function formatTimeHuman(time) {
  s = time%60;
  m = Math.floor((time%3600)/60);
  h = Math.floor((time%86400)/3600);
  s = s < 10 ? "0" + s : s;
  m = m < 10 ? "0" + m : m;
  h = h < 10 ? "0" + h : h;
  return h + ':' + m + ':' + s;
}

/**
 * Convert HH:MM:SS back to arbitrary seconds (not a timestamp).
 */
function formatTimeTimestamp(time) {
  var stamp = 0;
  var timeParts = time.split(":");
  if (timeParts[0]) {
    stamp += parseInt(timeParts[0]) * 3600;
  }
  if (timeParts[1]) {
    stamp += parseInt(timeParts[1]) * 60;
  }
  if (timeParts[2] * 1000) {
    stamp += parseInt(timeParts[2]);
  }
  return stamp;
};

})(jQuery, Drupal, this, this.document);

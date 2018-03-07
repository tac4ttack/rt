<?xml version="1.0" encoding="UTF-8"?>
<!-- Generated with glade 3.20.0 -->
<interface>
  <requires lib="gtk+" version="3.20"/>
  <object class="GtkAdjustment" id="adj_aa">
    <property name="lower">1</property>
    <property name="upper">3</property>
    <property name="value">1</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_blur">
    <property name="upper">10</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_cam_dir_x">
    <property name="lower">-180</property>
    <property name="upper">180</property>
    <property name="step_increment">5</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_cam_dir_y">
    <property name="lower">-180</property>
    <property name="upper">180</property>
    <property name="step_increment">5</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_cam_dir_z">
    <property name="lower">-180</property>
    <property name="upper">180</property>
    <property name="step_increment">5</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_cam_pos_x">
    <property name="lower">-10</property>
    <property name="upper">10</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_cam_pos_y">
    <property name="lower">-10</property>
    <property name="upper">10</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_cam_pos_z">
    <property name="lower">-10</property>
    <property name="upper">10</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_focus">
    <property name="lower">-10</property>
    <property name="upper">10</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_light_ambient">
    <property name="upper">10</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkAdjustment" id="adj_loop">
    <property name="lower">1</property>
    <property name="upper">5</property>
    <property name="value">1</property>
    <property name="step_increment">1</property>
    <property name="page_increment">10</property>
  </object>
  <object class="GtkWindow" id="window">
    <property name="visible">True</property>
    <property name="can_focus">False</property>
    <property name="title" translatable="yes">RT with gtk</property>
    <property name="resizable">False</property>
    <child>
      <object class="GtkGrid" id="grid">
        <property name="visible">True</property>
        <property name="can_focus">False</property>
        <child>
          <object class="GtkImage" id="img">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="stock">gtk-missing-image</property>
          </object>
          <packing>
            <property name="left_attach">1</property>
            <property name="top_attach">0</property>
          </packing>
        </child>
        <child>
          <object class="GtkBox">
            <property name="visible">True</property>
            <property name="can_focus">False</property>
            <property name="orientation">vertical</property>
            <child>
              <object class="GtkFrame" id="frm_scene">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkComboBoxText" id="cmb_scene">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="active">0</property>
                        <items>
                          <item translatable="yes">Select a scene</item>
                        </items>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Scene</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">0</property>
              </packing>
            </child>
            <child>
              <object class="GtkSeparator">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="margin_top">10</property>
                <property name="margin_bottom">10</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">1</property>
              </packing>
            </child>
            <child>
              <object class="GtkButtonBox">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="layout_style">start</property>
                <child>
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Modifications</property>
                  </object>
                  <packing>
                    <property name="expand">True</property>
                    <property name="fill">True</property>
                    <property name="position">0</property>
                  </packing>
                </child>
                <child>
                  <object class="GtkSwitch" id="switch_modif">
                    <property name="visible">True</property>
                    <property name="can_focus">True</property>
                  </object>
                  <packing>
                    <property name="expand">True</property>
                    <property name="fill">True</property>
                    <property name="position">1</property>
                  </packing>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">2</property>
              </packing>
            </child>
            <child>
              <object class="GtkSeparator">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="margin_top">10</property>
                <property name="margin_bottom">10</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">3</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frm_reflect">
                <property name="visible">True</property>
                <property name="sensitive">False</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkButtonBox">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="layout_style">start</property>
                        <child>
                          <object class="GtkLabel">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="label" translatable="yes">Reflection loop</property>
                          </object>
                          <packing>
                            <property name="expand">True</property>
                            <property name="fill">True</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkScale" id="scale_loop">
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="adjustment">adj_loop</property>
                            <property name="round_digits">1</property>
                            <property name="digits">0</property>
                          </object>
                          <packing>
                            <property name="expand">True</property>
                            <property name="fill">True</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Reflection</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">4</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frm_cam">
                <property name="visible">True</property>
                <property name="sensitive">False</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkBox">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="orientation">vertical</property>
                        <child>
                          <object class="GtkButtonBox">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="layout_style">start</property>
                            <child>
                              <object class="GtkLabel">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="label" translatable="yes">Position</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkScale" id="scale_cam_pos_x">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="adjustment">adj_cam_pos_x</property>
                                <property name="round_digits">1</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">1</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkScale" id="scale_cam_pos_y">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="adjustment">adj_cam_pos_y</property>
                                <property name="round_digits">1</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">2</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkScale" id="scale_cam_pos_z">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="adjustment">adj_cam_pos_z</property>
                                <property name="round_digits">1</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">3</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkButtonBox">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="layout_style">start</property>
                            <child>
                              <object class="GtkLabel">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="label" translatable="yes">Direction</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkScale" id="scale_cam_dir_x">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="adjustment">adj_cam_dir_x</property>
                                <property name="round_digits">1</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">1</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkScale" id="scale_cam_dir_y">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="adjustment">adj_cam_dir_y</property>
                                <property name="round_digits">1</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">2</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkScale" id="scale_cam_dir_z">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="adjustment">adj_cam_dir_z</property>
                                <property name="round_digits">1</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">3</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Camera</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">5</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frm_light">
                <property name="visible">True</property>
                <property name="sensitive">False</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkBox">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="orientation">vertical</property>
                        <child>
                          <object class="GtkColorButton" id="btn_color">
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="receives_default">True</property>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkScale" id="scale_color">
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="adjustment">adj_light_ambient</property>
                            <property name="round_digits">1</property>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Ambient lighting</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">6</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frm_cartoon">
                <property name="visible">True</property>
                <property name="sensitive">False</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkButtonBox">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="layout_style">start</property>
                        <child>
                          <object class="GtkLabel">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="label" translatable="yes">Activate</property>
                          </object>
                          <packing>
                            <property name="expand">True</property>
                            <property name="fill">True</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkSwitch" id="switch_cartoon">
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                          </object>
                          <packing>
                            <property name="expand">True</property>
                            <property name="fill">True</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Mode cartoon</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">7</property>
              </packing>
            </child>
            <child>
              <object class="GtkSeparator">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="margin_top">10</property>
                <property name="margin_bottom">10</property>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">8</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frm_effect">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkBox">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="orientation">vertical</property>
                        <child>
                          <object class="GtkButtonBox">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="layout_style">start</property>
                            <child>
                              <object class="GtkLabel">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="label" translatable="yes">Depth of field</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkSwitch" id="switch_dof">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">1</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkButtonBox">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="layout_style">start</property>
                            <child>
                              <object class="GtkLabel">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="label" translatable="yes">Focus</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkScale" id="scale_focus">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="adjustment">adj_focus</property>
                                <property name="round_digits">1</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">1</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkButtonBox">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="layout_style">start</property>
                            <child>
                              <object class="GtkLabel">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="label" translatable="yes">Blur</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkScale" id="scale_blur">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="adjustment">adj_blur</property>
                                <property name="round_digits">1</property>
                                <property name="digits">0</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">1</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">2</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Effects</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">9</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frm_filter">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkButtonBox">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="layout_style">start</property>
                        <child>
                          <object class="GtkLabel">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="label" translatable="yes">Filter</property>
                          </object>
                          <packing>
                            <property name="expand">True</property>
                            <property name="fill">True</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkComboBoxText" id="cmb_filter">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="active">0</property>
                            <items>
                              <item translatable="yes">None</item>
                              <item translatable="yes">Sepia</item>
                              <item translatable="yes">B&amp;W</item>
                            </items>
                          </object>
                          <packing>
                            <property name="expand">True</property>
                            <property name="fill">True</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Filters</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">10</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frm_aa">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkBox">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="orientation">vertical</property>
                        <child>
                          <object class="GtkButtonBox">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="layout_style">start</property>
                            <child>
                              <object class="GtkLabel">
                                <property name="visible">True</property>
                                <property name="can_focus">False</property>
                                <property name="label" translatable="yes">Activate</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkSwitch" id="switch_aa">
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">1</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Anti-aliasing</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">11</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frm_info">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkLabel" id="lbl_info">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Info</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">12</property>
              </packing>
            </child>
            <child>
              <object class="GtkFrame" id="frm_action">
                <property name="visible">True</property>
                <property name="can_focus">False</property>
                <property name="label_xalign">0</property>
                <property name="shadow_type">none</property>
                <child>
                  <object class="GtkAlignment">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="left_padding">12</property>
                    <child>
                      <object class="GtkBox">
                        <property name="visible">True</property>
                        <property name="can_focus">False</property>
                        <property name="orientation">vertical</property>
                        <child>
                          <object class="GtkButton" id="btn_draw">
                            <property name="label" translatable="yes">Draw scene</property>
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="receives_default">True</property>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">0</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkButton" id="btn_filter">
                            <property name="label" translatable="yes">Apply filter</property>
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="receives_default">True</property>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">1</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkButtonBox">
                            <property name="visible">True</property>
                            <property name="can_focus">False</property>
                            <property name="layout_style">expand</property>
                            <child>
                              <object class="GtkButton" id="btn_save">
                                <property name="label" translatable="yes">Save JPEG (fast)</property>
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="receives_default">True</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">0</property>
                              </packing>
                            </child>
                            <child>
                              <object class="GtkButton" id="btn_save2">
                                <property name="label" translatable="yes">Save BMP (slow)</property>
                                <property name="visible">True</property>
                                <property name="can_focus">True</property>
                                <property name="receives_default">True</property>
                              </object>
                              <packing>
                                <property name="expand">True</property>
                                <property name="fill">True</property>
                                <property name="position">1</property>
                              </packing>
                            </child>
                          </object>
                          <packing>
                            <property name="expand">False</property>
                            <property name="fill">True</property>
                            <property name="position">2</property>
                          </packing>
                        </child>
                        <child>
                          <object class="GtkButton" id="btn_quit">
                            <property name="label" translatable="yes">Quit</property>
                            <property name="visible">True</property>
                            <property name="can_focus">True</property>
                            <property name="receives_default">True</property>
                          </object>
                          <packing>
                            <property name="expand">True</property>
                            <property name="fill">True</property>
                            <property name="position">3</property>
                          </packing>
                        </child>
                      </object>
                    </child>
                  </object>
                </child>
                <child type="label">
                  <object class="GtkLabel">
                    <property name="visible">True</property>
                    <property name="can_focus">False</property>
                    <property name="label" translatable="yes">Actions</property>
                  </object>
                </child>
              </object>
              <packing>
                <property name="expand">False</property>
                <property name="fill">True</property>
                <property name="position">13</property>
              </packing>
            </child>
          </object>
          <packing>
            <property name="left_attach">0</property>
            <property name="top_attach">0</property>
          </packing>
        </child>
      </object>
    </child>
  </object>
  <object class="GtkTextBuffer" id="txt_info">
    <property name="text" translatable="yes">Salut !</property>
  </object>
</interface>

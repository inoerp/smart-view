<?php 
include_once 'basics.inc';
?>
readonly_field='<?php echo strip_tags(gettext('readonly field')); ?>'
select_bu_first="<?php echo gettext('Select BU First!'); ?>"
no_period_available_to_open="<?php echo gettext("No period avaibale to open"); ?>"
no_data_found="<?php echo gettext("No Data Found"); ?>"
invalid_value="<?php echo gettext("Invalid Value"); ?>"
invalid_data="<?php echo gettext("Invalid Data"); ?>"
move_line_wo_header="<?php echo !empty($site_info->move_line_wo_header) ? $site_info->move_line_wo_header : ''; ?>"
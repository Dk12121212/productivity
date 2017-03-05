<tr id="attr<?php print $row_number; ?>">
  <td>
    <?php print $row_number; ?>
  </td>
  <td width="30%">
    <select id="selectbasic" name="selectbasic" class="form-control" value="<?php print $tracking['project_nid']; ?>">
      <?php foreach ($projects as $key => $project): ?>
        <option value="<?php print $key; ?><"><?php print $project; ?></option>
      <?php endforeach; ?>
    </select>
  </td>
  <td width="7%">
    <input value="<?php print $tracking['issue']; ?>" type="text" name='issue' placeholder='#' class="form-control"/>
  </td>
  <td width="7%">
    <input value="<?php print $tracking['pr']; ?>" type="text" name='pr' placeholder='#' class="form-control"/>
  </td>
  <td width="51%">
    <input value="<?php print $tracking['title']; ?>" type="text" name='title' placeholder='Description' class="form-control"/>
  </td>
  <td width="5%">
    <input value="<?php print $tracking['length']; ?>" name="issue-time" type="number" step="0.10" min="0" placeholder="4" class="form-control input-md issue-time">
  </td>
</tr>
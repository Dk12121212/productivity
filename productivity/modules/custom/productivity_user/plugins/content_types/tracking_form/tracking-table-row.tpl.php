<tr id="attr<?php print $row_number; ?>" mlid="<?php print $tracking['mlid'] ? $tracking['mlid'] : 'new'; ?>">
  <td>
    <?php print $row_number; ?>
  </td>
  <td width="20%">
    <select id="selectProject" name="project" class="form-control" value="<?php print $tracking['project_nid']; ?>" <?php print $tracking['disabled']; ?>>
      <?php foreach ($projects as $key => $project): ?>
        <option value="<?php print $key; ?>"><?php print $project; ?></option>
      <?php endforeach; ?>
    </select>
  </td>
  <td width="12%">
    <input value="<?php print $tracking['repo']; ?>" type="text" name='repo' placeholder='Gizra/some-repo' class="form-control" <?php print $tracking['disabled']; ?>/>
  </td>
  <td width="7%">
    <input value="<?php print $tracking['issue']; ?>" type="text" name='issue' placeholder='#' class="form-control" <?php print $tracking['disabled']; ?>/>
  </td>
  <td width="7%">
    <input value="<?php print $tracking['pr']; ?>" type="text" name='pr' placeholder='#' class="form-control"/>
  </td>
  <td width="33%">
    <input value="<?php print $tracking['title']; ?>" type="text" name='title' placeholder='Description - Leave empty to get title of PR from GH ' class="form-control"/>
  </td>
  <td width="14%">
    <select id="selectType" name="type" class="form-control" value="<?php print $tracking['type']; ?>">
      <?php foreach ($types as $key => $type): ?>
        <option value="<?php print $key; ?>"><?php print $type; ?></option>
      <?php endforeach; ?>
    </select>
  </td>
  <td width="7%">
    <input value="<?php print $tracking['length']; ?>" name="issue-time" type="number" step="0.10" min="0" placeholder="4" class="form-control input-md issue-time">
  </td>
</tr>